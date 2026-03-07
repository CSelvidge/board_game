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

void move_fellowship_token(FellowshipToken *token, FellowshipToken *frodo, int8_t index, BoardState *board, const char zone_arrays[6][9], int8_t variance) {
    int8_t to_destination = ZONE_SIZE - (token->column + 1); //How far to get to current destination
    int8_t  passover = variance - to_destination; //How close the token gets to destination with incoming movement
    
    /*
        Fellowship tokens are required to move the full amount that they rolled even if it takes you past the current destination.
        The exception is Minas Morgul where the token "stops" on that board space but only Frodo may continue
        A special rule is then applied, that special rule is complex and will be added later
        Furthermore //TODO special rule
                                                                                                                                    */

    if (to_destination < variance && index != 4){
        if (token->row == ZONE_MINASMORGUL) {
            printf("You have arrived at Minas Morgul, only the ringbearer may continue from here.");
            token->column = 9;
            token->active = 0;
        } else {
            token->row++;
            token->column = passover;
            token->assisting = 0;
        }
    }

    if ((variance + (token->column + 1) > ZONE_SIZE)) {
        if (board->destination == MINASMORGUL && index != 4) {
            printf("You have arrived at Minas Morgul, only the ringbearer may continue from here->");
            token->column = 9;
            token->active = 0;
        }else {
            token->row++;
            int8_t remainder = ZONE_SIZE - (token->column + 1);
            token->column = variance - remainder;
        }
    } else if (variance + (token->column + 1) == ZONE_SIZE && board->destination != MINASMORGUL){ //Landed on the destination exactly, the board gains 1 courage, row not advanced until past destination
        update_courage(board, 1);
        token->column += variance;
    }else if(variance + (token->column + 1) == ZONE_SIZE && board->destination == MINASMORGUL && index != 4){ //Landed on Minas Morgul exactly, Frodo may advance an addition space towards mount doom for free
        printf("You have arrived at Minas Morgul via exact roll, your valor has allowed the ringbearer to advance further towards Mount Doom when he arrives!");
        board->frodo_advance++;
        token->active = 0;
    }else if (variance + (token->column + 1) == ZONE_SIZE && board->destination == MINASMORGUL && index == 4){
        printf("The ringbearer has arrived at Minas Morgul, the fate of Middle Earth is now in his hands-> Dut to the gallantry of the fellowship, he may advance %hhd spaces->", board->frodo_advance);
    }else {
        token->column += variance;
    }

    if (zone_arrays[token->row][token->column] == 'N' || zone_arrays[token->row][token->column == 'C']) {
        //TODO add logic here to check if the displayed character is another fellowship member OR hardcore is on
        //While a fellowship member occupies a special board space, and it is not hardcore, the space effect will not trigger again
        //So basically trigger a break
        //Project not at the point where displaying the game is implimented
        if(zone_arrays[token->row][token->column] == 'N') {
        update_nazgul(board, 1);
        } else if (zone_arrays[token->row][token->column] == 'C') {
        update_courage(board, -1);
        }
    }

    if(token->row < frodo->row || (token->row == frodo->row && token->column < frodo->column)) {
        token->assisting = 0;
    }
}

/*j is the incriment variable, i is the index into the larger encounter_card_defs[42] array.
  This allows the zone cards to be replaced by the next 7 cards from the larger array
  NOTE: this will be the same every time, shuffling is needed */
void update_zone(BoardState *board, int8_t zone_cards[]) {
    uint8_t start = ZONE_SIZE * board->current_zone;
    for (uint8_t j = 0; j < ZONE_SIZE; j++) {
        uint8_t i = start + j;
        zone_cards[j] = i;
    }

    board->current_zone++;
    board->destination++;
}

const char zone_arrays[6][9] =
{
    {'R', '-', '-', 'N', '-', '-', '-', 'C', 'L'}, //Zone 0 from Rivendell to Lothlorian

    {'L', '-', 'C', '-', '-', '-', '-', 'N', 'R'}, //Zone 1 from Lothlorian to Rohan

    {'R', '-', '-', '-', 'N', '-', 'C', '-', 'H'}, //Zone 2 from Rohan to Helm's Deep

    {'H', '-', '-', 'C', '-', '-', 'N', '-', 'G'}, //Zone 3 from Helm's Deep to Gondor

    {'G', 'C', '-', 'N', '-', 'N', '-', '-', 'M'}, //Zone 4 from Gondor to Minas Morgul

    {'M', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'D'} //Zone 5 from Minas Morgul to Mount Doom

};
