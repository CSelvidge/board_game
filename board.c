#include "board.h"

/*
---------- Library for the creation and maintenance of the board ----------
           Including token location, board space attributes, current destination
           Cards are handled seperately
*/

BoardState init_board() {
    BoardState board = {
        .current_zone = 0,
        .destination = 0,
        .courage = 13,
        .uruk_hai_count = 1,
        .nazghul_count = 1,
        .flags = 0,
        .frodo_advance = 0
    };

    return board;
}

int8_t update_courage(BoardState *board, int8_t variance) {
    board->courage += variance;
    if (board->courage <= 0) {
        printf("The Fellowship's courage has faltered. The game is over, and Sauron has won.\n");
        return 1;
    }
    return 0;
}

int8_t update_nazgul(BoardState *board, int8_t variance) {
    board->nazghul_count += variance;
    if (board->nazghul_count >= NAZGHUL_MAX && !(board->flags & BF_EOWYNN)) {
        printf("The Nazgul have overwhelmed the Fellowship. The game is over, and Sauron has won.\n");
        return 1;
    }
    return 0;
}


void move_fellowship_roll(FellowshipToken fellowship[], FellowshipToken *frodo, int8_t index, BoardState *board, const char zone_arrays[6][9], int8_t variance) {
    FellowshipToken *token = &fellowship[index];
    int8_t new_col = token->column + variance;

    /*
        Fellowship tokens are required to move the full amount that they rolled even if it takes you past the current destination.
        The exception is Minas Morgul where the token "stops" on that board space but only Frodo may continue
        A special rule is then applied, that special rule is complex and will be added later
        Furthermore //TODO special rule                                         
                                                                                                                                */

    if (new_col >= ZONE_SIZE) {
        int8_t exact_roll = (new_col == ZONE_SIZE);

        if (exact_roll) {
            if (token->row == ZONE_GONDOR) {
                printf("You have arrived at Minas Morgul via exact roll, your valor has allowed the ringbearer to advance further towards Mount Doom when he arrives!");
                board->frodo_advance++;
                token->active = 0;
                token->assisting = 0;
                token->column = ZONE_SIZE - 1;
                return;
            } else {
            update_courage(board, 1);
            token->row++;
            token->column = 0;
            return;
            }
        } else if (token->row == ZONE_GONDOR){
            printf("You have arrived at Minas Morgul, only the ringbearer may continue.");
            token->active = 0;
            token->assisting = 0;
            token->column = new_col - ZONE_SIZE;
            return;
        } else {
            token->row++;
            token->column = new_col - ZONE_SIZE;
        }
    } else {
        token->column = new_col;
    }

    token->assisting = (token->row == frodo->row && token->column >= frodo->column);

    char board_space = zone_arrays[token->row][token->column];
    int8_t occupied = 0;
    for (int8_t i = 0; i < 5; i++) {
        if (i == index) continue;
        if (fellowship[i].row == token->row && fellowship[i].column == token->column) {
            occupied = 1;
            break;
        }
    }

    if (!occupied || (board->flags & BF_HARDCORE)) {
        if (board_space == 'N') update_nazgul(board, 1);
        if (board_space == 'C') update_courage(board, -1);
    }
}

void move_frodo_roll(FellowshipToken fellowship[], FellowshipToken *frodo, int8_t index, BoardState *board, const char zone_arrays[6][9], int8_t variance) {
    FellowshipToken *frodo = &fellowship[4];
    int8_t new_col = frodo->column + variance;

    if (new_col >= ZONE_SIZE) {
        int8_t exact_roll = 0;

        if (exact_roll) {
            if (frodo->row == ZONE_GONDOR) {
                printf("The ringbearer has arrived at Minas Morgul, the fate of Middle Earth rests in their hands.");
                if (board->frodo_advance) {
                    printf("The gallantry of the Fellowship allows frodo to advance %d spaces.", board->frodo_advance);
                }
                frodo->row++;
                frodo->column = 0;
                return;
            } else {
                printf("The ringbearer has arrived at the destination via exact roll, a gandalf card has been awarded.");
                frodo->row++;
                frodo->column = 0;
                board->destination++;
                board->current_zone++;
                //TODO draw gandalf card
                return;
            }
        } else {
            printf("The ringbearer has arrived at the destination, the next leg of the journey is upon you.");
            frodo->row++;
            frodo->column = 0;
            board->destination++;
            board->current_zone++;
            return;
        }
    } else {
        frodo->column = new_col;
    }

    char board_space = zone_arrays[frodo->row][frodo->column];
    int8_t occupied = 0;
    for (int8_t i = 0; i < 5; i++) {
        if (i == index) continue;
        if (fellowship[i].row == frodo->row && fellowship[i].column == frodo->column) {
            occupied = 1;
            break;
        }
    }

    if (!occupied || (board->flags & BF_HARDCORE)) {
        if (board_space == 'N') update_nazgul(board, 1);
        if (board_space == 'C') update_courage(board, -1);
    }
}

/*j is the incriment variable, i is the index into the larger encounter_card_defs[42] array.
  This allows the zone cards to be replaced by the next 7 cards from the larger array
  NOTE: this will be the same every time, shuffling is needed */
void update_zone(BoardState *board, int8_t zone_cards[]) {
    uint8_t start = ZONE_CARD_SIZE * board->current_zone;
    for (uint8_t j = 0; j < ZONE_CARD_SIZE; j++) {
        uint8_t i = start + j;
        zone_cards[j] = i;
    }

    board->current_zone++;
    board->destination++;
}

const char zone_arrays[6][9] =
{
    {'R', '-', '-', 'N', '-', '-', '-', 'C', 'L'}, //Zone 0 from Rivendell to Lothlorian

    {'L', '-', 'C', '-', '-', '-', '-', 'N', 'A'}, //Zone 1 from Lothlorian to Rohan

    {'A', '-', '-', '-', 'N', '-', 'C', '-', 'H'}, //Zone 2 from Rohan to Helm's Deep

    {'H', '-', '-', 'C', '-', '-', 'N', '-', 'G'}, //Zone 3 from Helm's Deep to Gondor

    {'G', 'C', '-', 'N', '-', 'N', '-', '-', 'M'}, //Zone 4 from Gondor to Minas Morgul

    {'M', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'D'} //Zone 5 from Minas Morgul to Mount Doom

};
