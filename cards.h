#include <stdint.h>

typedef struct {
    const char *name;
    const char *text;
}EncounterCardDef;

typedef struct { //4 bytes so 16 per cache line
    uint8_t alignment; // 0 Foe, 1 Friend, 2 Special mordor card
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
    uint8_t  discarded; // Card still in play or not
}GandalfCardState;

void init_enconter_states(EncounterCardState encounter_card_states[42]); //States are mutable so they should not be initialized via const

const GandalfCardDef gandalf_card_defs[5];
const GandalfCardState gandalf_card_states[5];
const EncounterCardDef boromir;
const EncounterCardVars boromir_vars;
EncounterCardState boromir_state;
const EncounterCardDef encounter_card_defs[42];
const EncounterCardVars encounter_card_vars[42];
EncounterCardState encounter_card_states[42];
