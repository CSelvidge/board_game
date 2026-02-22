#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "board.h"
#include "cards.h"
#include "dice.h"
#include "tokens.h"

#define ENCOUNTER_CARD_LEN 7
#define NAZGHUL_MAX 9
#define URUKHAI_MAX 6
#define MAX_PLAYERS 4
#define NAME_LEN 32

void get_player_names(int8_t num_players, char player_names[MAX_PLAYERS][NAME_LEN]);
void clear_buffer();
int8_t greeting();


int main(void) {
    /*********************
    ----------TODO ----------
    Define dice:
    1 - Fellowship movement dice (gimli, legolas, arigorn, M&P, F&S) -- I believe this is done
    2 - Combat die (Aragorn, legolas, gimli, M&P, Sauron, Gandalf) -- I believe this is done
    3 - Encounter number dice (2 dice standard ints 1 - 6) -- I believe this is done

    Define tokens:
    1 - Urak-hai (5 Standard 1 Cheiftan) ------------ See following comment
    2 - Nazghul (8 standard 1 Witch King) -- I do not believe these tokens need to exist in a defined state,
                                            However a struct may need to exist for board position or token art assets in future
    3 - Fellowship members (Gimli, Aragorn, Legolas, M&P, F&S) - State struct is required for current position and to easily check to see if can assist in combat etc.
                                                                Make this struct LIGHT and CACHE friendly

    4 - Gandalf and Treebird tokens DON'T FORGET -- These are covered as bitflags in the BoardState struct,
                                                    but art assets may require a struct state
    
    Define cards:
    Card sets per each destination zones (Rivendell - > Minas Morgul) -- I can see no way but to hardcode definitions for all cards, seperated by zone, into arrays.
                                                                        Consider a master array, or avoiding that, use enum Zone in board.h
    Don't forget Boromir
    Gandalf cards -- I belive this is done

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
    srand(time(NULL));
    num_players = greeting(); // Greeting function ensures correct number of players(1 - 4)
    char player_names[MAX_PLAYERS][NAME_LEN] = {0};

    get_player_names(num_players, player_names);

    const char* fellowship_names[] = {'Aragorn', 'Gimli', 'Legolas', 'Marry and Pippen', 'Frodo and Samwise'};
    Die fellowship_dice[5];

    for (uint8_t i = 0; i < 5; i++) {
        fellowship_dice[i] = init_standard_die();
    }

    EncounterCardDef boromir_def;
    boromir_def = init_boromir_def(boromir_def);


    EncounterCardState boromir_state = {
        .flags = 1,
        .owned_by = 0
    };

    EncounterCardDef all_encounter_defs[42] = {0}; //Initialize safely, zone cards will be in sets of 7, so every 7 cards is a new zone
    EncounterCardState all_encounter_states[42] = {0};
    uint8_t zone_cards[7] = {0}; //7 indexes into the all_encounter_defs to define cards in the zone
    GandalfCardDef gandalf_cards[5];
    GandalfCardState gandalf_card_states[5];
    init_gandalf_cards(gandalf_cards, gandalf_card_states);

    BoardState board = init_board();

    Die e_die_1 = init_standard_die();
    Die e_die_2 = init_standard_die();
    Die combat_die = init_combat_die();

    return 0;
}


void get_player_names(int8_t num_players, char player_names[][NAME_LEN]) {

    for (int8_t i = 0; i < num_players; i++) {
        char confirmed = 'n';
        while (confirmed != 'y' && confirmed != 'Y'){
            printf("Please enter the name of player %d: ", i + 1);
            if (fgets(player_names[i], NAME_LEN, stdin) != NULL) {
                player_names[i][strcspn(player_names[i], "\n")] = '\0';
            }
            printf("Is the name '%s' correct for player %d? (y/n): ", player_names[i], i + 1);
            confirmed = getchar();
            clear_buffer();
        }
    }

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
