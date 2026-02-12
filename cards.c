/*
---------- Creation of cards via structs ----------
           Create sets of cards for each destination zone, and gandalf cards 
           Do not forget boromir         
*/


typedef struct {
    char* text;
    char* card_name;
    char* owned_by; //Which player is the friend card assigned to
    unsigned char alignment; // Friend, Foe,  or Special mordor card
    unsigned char displayed; // Card flipped or not
    unsigned char discarded; // Card still in play or not
    unsigned char is_combat; // Does the card invoke combat
    unsigned char total_combats; // If it does how many
}Encounter_card;

typedef struct {
    char* text;
    unsigned char discarded; // Card still in play or not
}Gandalf_card;
