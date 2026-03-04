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
        .flags = 0
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

void move_fellowship_token(FellowshipToken token,const char zone_arrays[6][9], unsigned char battle_helpers[]) {
    //Check if movedment takes you past the current destination, or if you are behind the ring bearer
    //Not implimented as of now
    ;
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
