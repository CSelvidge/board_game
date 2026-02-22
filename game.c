#include "game.h"

void clear_buffer() {
    char c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}


void start_game(int8_t num_players, char player_names[MAX_PLAYERS][NAME_LEN]) {
    /*Init all the bullshit here
      Not intended to be the entry point into the loop
                                                        */


    /*Die initialization is all 5 fellowship, 2 encounter, and 1 combat*/
    const char* fellowship_names[] = {"Aragorn", "Gimli", "Legolas", "Marry and Pippen", "Frodo and Samwise"};
    Die fellowship_dice[5];
    for (uint8_t i = 0; i < 5; i++) {
        fellowship_dice[i] = init_standard_die();
    }

    Die encounter_die[2];
    for (uint8_t i = 0; i < 2; i++) {
        encounter_die[i] = init_standard_die();
    }

    Die combat_die = init_combat_die();

    /*Boromir is a unique card so it has to be initialized outside of standard cards*/
    EncounterCardDef* boromir_def;
    EncounterCardState* boromir_state;
    init_boromir(boromir_def, boromir_state);

    EncounterCardDef all_encounter_defs[42] = {0}; //Initialize safely, zone cards will be in sets of 7, so every 7 cards is a new zone
    EncounterCardState all_encounter_states[42] = {0};
    uint8_t zone_cards[7] = {0}; //7 indexes into the all_encounter_defs to define cards in the zone
    GandalfCardDef gandalf_cards[5];
    GandalfCardState gandalf_card_states[5];
    init_gandalf_cards(gandalf_cards, gandalf_card_states);

    BoardState board = init_board();

    
}
