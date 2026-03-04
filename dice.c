#include "dice.h"

const char *name_sides[] = {"Aragorn", "Gimli", "Legolas", "Marry and Pippen", "Sauron", "Gandalf"};
int8_t rolls[5] = {0};
uint8_t number_sides[] = {1, 2, 3, 4, 5, 6};

const Die combat_die = {
    .nsides = DICE_SIDES,
    .side_type = SIDE_STR,
    .sides = name_sides
};

const Die standard_die = {
    .nsides = DICE_SIDES,
    .side_type = SIDE_U8,
    .sides = number_sides
};

/*This works because all dice are D6, so we only need the amount of dice and their corresponding rolls
  The rolls array will always be max size, we just index into it as needed as the new rolls are replacing old ones from index 0->up*/
void roll_dice(int8_t count, int8_t rolls[]) {
    for (uint8_t i = 0; i < count; i++) {
        rolls[i] = rand() % 6; //This corresponds to lookup arrays that are index 0 - 5 on the dice structs themselves
    }
}
