#include <stdio.h>
#include "board.h"
#include "cards.h"
#include "dice.h"
#include "tokens.h"


#define STAGES
#define ENCOUNTER_CARD_LEN 7;
#define NAZGHUL_MAX 9;
#define URUKHAI_MAX 6;


int main(void) {
    /*********************
    ----------TODO ----------
    Define dice:
    1 - Fellowship movement dice (gimli, legolas, arigorn, M&P, F&S)
    2 - Combat die (Aragorn, legolas, gimli, M&P, Sauron, Gandalf)
    3 - Encounter number dice (2 dice standard ints 1 - 6)

    Define tokens:
    1 - Urak-hai (5 Standard 1 Cheiftan)
    2 - Nazghul (8 standard 1 Witch King)
    3 - Fellowship members (Gimli, Aragorn, Legolas, M&P, F&S)
    4 - Gandalf and Treebird tokens DON'T FORGET
    
    Define cards:
    Card sets per each destination zones (Rivendell - > Minas Morgul)
    Don't forget Boromir
    Gandalf cards

    Define board:
    Perhaps an array for the spaces between destination spaces. Index is the distance from the previous destination and the array itself can use [0,1,2] as unsigned chars
                                                                                                                                                 0 for standard square
                                                                                                                                                 1 for hope loss space
                                                                                                                                                 2 nazghul space
    
    Array of known destinations, or maybe a struct holds the destinations, won't know till we start.
    Array of characters that can assist the ring bearer in combat

    define structs:
    Cards will probably need to be a struct with a Text, Alignment, Zone, maybe art asset picture later?
    Characters will probably need to be structs that way we can easily connect them to dice sides and tokens for map movement


    Define rules:
    This is going to take some time, careful switch blocks and checks. Define dice before this so you can at least test those two things together.
    *********************/
    char* fellowship_names[] = {'Aragorn', 'Gimli', 'Legolas', 'Marry and Pippen', 'Frodo and Samwise'};
    EncounterCardDef all_encounter_cards[6][7];

    BoardState board = init_board();

    Encounter_die e_die_1 = init_encounter_die();
    Encounter_die e_die_2 = init_encounter_die();
    Combat_die combat_die = init_combat_die(fellowship_names);

    return 0;
}
