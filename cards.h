typedef struct {
    const char *name;
    const char *text;
    unsigned char alignment; // 0 Foe, 1 Friend,2 Special mordor card
    unsigned char special_effect; // 0 is just text, 1 is combat, 2 is courage, 3 is uruk hai, 4 is nazghul
    signed char effect_variance; //How many combats, how much courage, or how much urukhai or nazghul to add
}EncounterCardDef;

typedef struct {
    unsigned char flags; // 0 not displayed, 1 displayed, 2 is discarded
    unsigned char owned_by; //Which player is the friend card assigned to
}EncounterCardState;

typedef struct {
    char* title;// 8 bytes
    char* text;
}GandalfCardDef;

typedef struct {
    unsigned char discarded; // Card still in play or not
}GandalfCardState;


void init_gandalf_cards(GandalfCardDef card_defs[], GandalfCardState card_states[]);
EncounterCardDef init_boromir_def(EncounterCardDef boromir);
