#include <stdint.h>
#include <stdlib.h>

#define BOARD_OWNED 255 //Cards that are not owned by a player will default to being owned by the board
#define ENCOUNTER_LEN 42
#define GANDALF_LEN 5
#define ZONE_SIZE 7

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
    uint8_t  discarded; // Card still in play or not
}GandalfCardState;

void init_encounter_states(EncounterCardState encounter_card_states[ENCOUNTER_LEN]); //States are mutable so they should not be initialized via const
void shuffle_cards(uint8_t zone_cards[ZONE_SIZE]);

uint8_t zone_cards[7];
const GandalfCardDef gandalf_card_defs[GANDALF_LEN];
GandalfCardState gandalf_card_states[GANDALF_LEN];
const EncounterCardDef boromir;
const EncounterCardVars boromir_vars;
EncounterCardState boromir_state;
const EncounterCardDef encounter_card_defs[ENCOUNTER_LEN];
const EncounterCardVars encounter_card_vars[ENCOUNTER_LEN];
EncounterCardState encounter_card_states[ENCOUNTER_LEN];
