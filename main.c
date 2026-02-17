#include <stdio.h>
#include <stdint.h>
#include "board.h"
#include "cards.h"
#include "dice.h"
#include "tokens.h"


#define STAGES
#define ENCOUNTER_CARD_LEN 7;
#define NAZGHUL_MAX 9;
#define URUKHAI_MAX 6;

void get_player_names();
int8_t greeting();


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
    int8_t num_players;
    num_players = greeting();
    char* player_names[num_players];

    prepare_game_assets();
    const char* fellowship_names[] = {'Aragorn', 'Gimli', 'Legolas', 'Marry and Pippen', 'Frodo and Samwise'};
    Die fellowship_dice[5];

    for (uint8_t i = 0; i < 5; i++) {
        fellowship_dice[i] = init_standard_die();
    }

    EncounterCardDef all_encounter_cards[6][7];
    GandalfCardDef gandalf_cards[5];
    GandalfCardState gandalf_card_states[5];
    init_gandalf_cards(gandalf_cards, gandalf_card_states);

    BoardState board = init_board();

    Die e_die_1 = init_standard_die();
    Die e_die_2 = init_standard_die();
    Die combat_die = init_combat_die();

    return 0;
}

void prepare_game_assets() {

}

void get_player_names() {

}

void clear_buffer() {
    char c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int8_t greeting() {
    int8_t num_players;

    while (1) {
        printf("Welcome to the REPL version of Adventure to Mount doom.\nHow many players are playing? (1-4)\n: ");
        if (scanf("%hhd", &num_players) != 1) {
            printf("Invalid input, please enter a number between 1 and 4.\n");
            clear_buffer();
            continue;
        }

        if (num_players < 1 || num_players > 4) {
            printf("Invalid number of players, the game only supports 1-4 players.\n");
            clear_buffer();
            continue;
        }
        break;
    }

    clear_buffer();
    const char plural = num_players > 1 ? "s" : "";
    printf("Game will be setup for %d player%s.\n", num_players, plural);
    return num_players;
}
