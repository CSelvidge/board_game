#include "game.h"
#include "board.h"
#include "dice.h"
#include "cards.h"

void start_game(int8_t greeting_arr[], char player_names[MAX_PLAYERS][NAME_LEN]) {
    BoardState board;
    init_board(&board);

    int8_t num_players = greeting_arr[0];
    const char* fellowship_names[] = {"Aragorn", "Gimli", "Legolas", "Marry and Pippen", "Frodo and Samwise"};

    uint8_t zone_cards[7] = {0}; //7 indexes into the all_encounter_defs(cards.c) to define cards in the zone
    if (greeting_arr[1]) { //If hardcore mode is enabled, we need to track which player owns which friend cards for combat purposes
        uint8_t player_friends[MAX_PLAYERS][9] = {0}; //9 friend cards is the max in the game, hardcore mode forces players to only use the friends THEY own
    } else {
        uint8_t global_friends[9] = {0};
    }

    int8_t playing = 1;
    /*Game loop time!*/
    shitfuckass
    while (playing) {

    }

    
}


int8_t play_again() {
    printf("Do you want to play again? (y/n): ");
    char confirmation = getchar();
    if (confirmation == 'y' || confirmation == 'Y') {
        printf("Are the same players playing again? (y/n): ");
        clear_buffer();
        confirmation = getchar();
        if (confirmation == 'y' || confirmation == 'Y') {
            clear_buffer();
            return 2; //Indiciating we wish to reuse the current players
        } else {
            clear_buffer();
            return 1;
        }
    }
    clear_buffer();
    return 0;
}

void clear_buffer() {
    char c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}
