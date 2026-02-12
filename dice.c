/*
---------- Create dice ----------
           Fellowship movement dice
           Encounter number dice
           Combat die (singular)
*/

typedef struct {
    //uint32_t die_color; // Not used in initial REPL version, but once we move to art assets this can be used to color the die
    char* name;
    unsigned char sides[6];
} Fellowship_die;

typedef struct {
    char *names[6];
}Combat_die;

typedef struct {
    unsigned char sides[6];
}Encounter_die;

Encounter_die init_encounter_die() {
    Encounter_die die  = {{1, 2, 3, 4, 5, 6}};
    return die;
}

Combat_die init_combat_die(char* character_names) {
    Combat_die die;
    for ( char i = 0; i < 6; i++) {
        die.names[i] = character_names[i];
    }
    return die;
}

Fellowship_die init_fellowship_die(char* character_name) {
    Fellowship_die die = {
    .name = character_name,
    .sides = {1, 2, 3, 4, 5, 6}
    };
    return die;
}
