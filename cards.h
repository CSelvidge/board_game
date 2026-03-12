#ifndef CARDS_H
#define CARDS_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define BOARD_OWNED 255 //Cards that are not owned by a player will default to being owned by the board
#define ENCOUNTER_LEN 42
#define GANDALF_LEN 5
#define ZONE_CARD_SIZE 7

typedef struct {
    const char *name; //8 bytes
    const char *text;
}EncounterCardDef;

typedef struct { //4 bytes so 16 per cache line
    uint8_t alignment; // 0 Foe, 1 Friend, 3 Special mordor card
    uint8_t special_effect; // 0 is just text, 1 is combat, 2 is courage, 3 is uruk hai, 4 is nazghul
    int8_t combats; //Some cards have multiple combats 
    int8_t effect_variance; //How many combats, how much courage, or how much urukhai or nazghul to add
    uint8_t discardable; //Some cards are not removed once performed, some are
}EncounterCardVars;

typedef struct { //2 bytes so 32 per cache line
    uint8_t flags; // 0 not displayed, 1 displayed, 2 is discarded
    uint8_t  owned_by; //Which player is the friend card assigned to
}EncounterCardState;

typedef struct {
    char* title;// 8 bytes
    char* text;
}GandalfCardDef;

typedef struct {
    uint8_t discarded; // Card used / discarded
    uint8_t in_play; //Card in the player's hand
}GandalfCardState;

void init_encounter_states(EncounterCardState encounter_card_states[ENCOUNTER_LEN]); //States are mutable so they should not be initialized via const
void shuffle_cards(uint8_t cards[], size_t card_amount);
int8_t draw_gandalf_card(uint8_t gandalf_cards[]);

extern uint8_t zone_cards[7];
extern uint8_t gandalf_cards[5];
extern const GandalfCardDef gandalf_card_defs[GANDALF_LEN];
extern GandalfCardState gandalf_card_states[GANDALF_LEN];
extern const EncounterCardDef boromir;
extern const EncounterCardVars boromir_vars;
extern EncounterCardState boromir_state;
extern const EncounterCardDef encounter_card_defs[ENCOUNTER_LEN];
extern const EncounterCardVars encounter_card_vars[ENCOUNTER_LEN];
extern EncounterCardState encounter_card_states[ENCOUNTER_LEN];

#endif
