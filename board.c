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
        .nazghul_count = 0,
        .flags = 0
    };

    return board;
}

void update_courage(BoardState *board, int x) {
    board->courage += x; //Handles neaative and positive x, giuven via card's effect_variance
}

void move_fellowship_token(int x, unsigned char zone_spaces[], unsigned char battle_helpers[]) {
    //Check if movedment takes you past the current destination, or if you are behind the ring bearer
    if ((x + current_place) > 
}
