#include "dice.h"

/*
---------- Create dice ----------
           Fellowship movement dice
           Encounter number dice
           Combat die (singular)
*/

Encounter_die init_encounter_die() {
    Encounter_die die  = {{1, 2, 3, 4, 5, 6}};
    return die;
}

Combat_die init_combat_die(char* character_names[]) {
    Combat_die die;
    for ( char i = 0; i < 4; i++) {
        die.sides[i] = character_names[i];
    }
    die.sides[4] = 'Sauron';
    die.sides[5] = 'Gandalf';
    return die;
}

Fellowship_die init_fellowship_die(char* character_name) {
    Fellowship_die die = {
    .name = character_name,
    .sides = {1, 2, 3, 4, 5, 6}
    };
    return die;
}

void roll_die(void* die, ...);
