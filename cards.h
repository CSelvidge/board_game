typedef struct {
    const char *name;
    const char *text;
    unsigned char alignment; // 0 Foe, 1 Friend,2 Special mordor card
    unsigned char special_effect; // 0 is just text, 1 is combat, 2 is courage
    signed char effect_variance; //How many combats or how much courage is changed
}EncounterCardDef;

typedef struct {
    unsigned char flags; // 0 not displayed, 1 displayed, 2 is discarded
    unsigned char owned_by; //Which player is the friend card assigned to
}EncounterCardState;

typedef struct {
    char* text;
    unsigned char discarded; // Card still in play or not
}GandalfCard;
shit fuck ass
