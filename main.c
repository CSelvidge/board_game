#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "game.h"


void get_player_names(int8_t num_players, char player_names[MAX_PLAYERS][NAME_LEN]);
int8_t greeting();
int8_t ask_hardcore();

int main(void) {
    srand(time(NULL));
    int8_t active = (PLAY_AGAIN | FRESH);
    int8_t num_players = 0;
    int8_t hardcore = 0;
    char player_names[MAX_PLAYERS][NAME_LEN] = {0};

    /*This loop into switch dictates if the game should continue, be reset, or exit*/
    while (active) {
    if (active & PLAY_AGAIN){
        if ((active & FRESH) || !(active & SAME_PLAYERS)) {
            num_players = greeting();
            get_player_names(num_players, player_names);
        }

        if (active & FRESH) {
            hardcore = ask_hardcore();
        } else if (active & TOGGLE_HARDCORE) {
            hardcore = !hardcore;
        }
    }
        start_game(num_players, hardcore, player_names);
        active = play_again(); //returns active as bitpacked
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
    int8_t num_players = 0;
    while (1) {
        printf("Welcome to the REPL version of Adventure to Mount doom.\nHow many players are playing? (1-4)\n: ");
        if (scanf("%hhd", num_players) != 1) {
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

int8_t ask_hardcore() {
    printf("Do you want to play hardcore?");
    char confirmation = getchar();
    if (confirmation == 'y' || confirmation == 'Y') {
        return 1;
    }

    return 0;
}



