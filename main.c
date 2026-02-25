#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "game.h"

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
    srand(time(NULL));
    int8_t active = 1;
    int8_t num_players;
    char player_names[MAX_PLAYERS][NAME_LEN] = {0};
    BoardState board;

    /*This loop dictates if the game should continue, be reset, or exit*/
    while (active) {
        if (active == 1) {
            num_players = greeting();
            get_player_names(num_players, player_names);
        }

        init_board(&board);
        play_game(&board, num_players, player_names);

        active = play_again(); //returns yes to start a new loop, 0 to end the loop and exit,
                               //a return greater than 1 indicates we want to reuse the same players
    }

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
