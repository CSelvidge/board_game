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
        }else if (active & TOGGLE_HARDCORE) {
            hardcore = !hardcore;
        }
    }
        start_game(num_players, hardcore, player_names);
        active = play_again(hardcore); //returns active as bitpacked
    }

    return 0;
}

void get_player_names(int8_t num_players, char player_names[][NAME_LEN]) {
    char confirmation[8] = {0};
    char message[128] = {0};

    for (int8_t i = 0; i < num_players; i++) {
        snprintf(message, sizeof(message), "Please enter the name of player %d: ", i + 1);
        get_user_input(message, player_names[i], NAME_LEN);

        snprintf(message, sizeof(message), "You entered %s, is that correct? (y/n): ", player_names[i]);
        get_user_input(message, confirmation, sizeof(confirmation));

        while (confirmation[0] != 'y' && confirmation[0] != 'Y') {
            snprintf(message, sizeof(message), "Please enter the name of player %d: ", i + 1);
            get_user_input(message, player_names[i], NAME_LEN);
            snprintf(message, sizeof(message), "You entered %s, is that correct? (y/n): ", player_names[i]);
            get_user_input(message, confirmation, sizeof(confirmation));
        }
    }
}

int8_t greeting() {
    char confirmation[8] = {0};
    while (1) {
        get_user_input("Welcome to the REPL version of Adventure to Mount doom.\nHow many players are playing? (1-4): ", confirmation, sizeof(confirmation));
        confirmation[0] = (confirmation[0] - '0'); //Convert ascii to pure int form

        if (confirmation[0] < 1 || confirmation[0] > 4) {
            printf("Invalid number of players, the game only supports 1-4 players.\n");
            continue;
        }

        break;

    }

    const char *plural = confirmation[0] > 1 ? "s" : "";
    printf("Game will be setup for %d player%s.\n", confirmation[0], plural);
    return confirmation[0]; //Portable because if the system implimentation is signed or unsigned char 1-4 fits in int8_t
}

int8_t ask_hardcore() {
    char confirmation[8] = {0};
    get_user_input("Do you want to play hardcore? (y/n): ", confirmation, sizeof(confirmation));
    if (confirmation[0] == 'y' || confirmation[0] == 'Y') {
        return 1;
    }

    return 0;
}



