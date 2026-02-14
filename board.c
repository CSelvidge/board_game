#include "board.h"

/*
---------- Library for the creation and maintenance of the board ----------
           Including token location, board space attributes, current destination
           Cards are handled seperately
*/

void init_board() {
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
