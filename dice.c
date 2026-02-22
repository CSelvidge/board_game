#include "dice.h"

/*
---------- Create dice ----------
           Fellowship movement dice
           Encounter number dice
           Combat die (singular)
*/

Die init_standard_die() {
    Die die  = {
        .nsides = DICE_SIDES,
        .side_type = SIDE_U8,
        .sides = number_sides
    };
    return die;
}

Die init_combat_die() {
    Die die = {
        .nsides = DICE_SIDES,
        .side_type = SIDE_STR,
        .sides = name_sides
    };
    return die;
}

void roll_dice(Die dice[], uint8_t count, uint8_t rolls[]) {

    for (uint8_t i = 0; i < count; i++) {
        rolls[i] = rand() % 6; //This corresponds to lookup arrays that are index 0 - 5, ALL dice in this program are a D6
    }
}
