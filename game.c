#include "game.h"

void clear_buffer() {
    char c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}


void start_game(int8_t num_players, char player_names[MAX_PLAYERS][NAME_LEN]) {
    /*Init all the bullshit here
      Not intended to be the entry point into the loop
                                                        */


    /*Die initialization is all 5 fellowship, 2 encounter, and 1 combat*/
    const char* fellowship_names[] = {"Aragorn", "Gimli", "Legolas", "Marry and Pippen", "Frodo and Samwise"};
    Die fellowship_dice[5];
    for (uint8_t i = 0; i < 5; i++) {
        fellowship_dice[i] = init_standard_die();
    }

    Die encounter_die[2];
    for (uint8_t i = 0; i < 2; i++) {
        encounter_die[i] = init_standard_die();
    }

    Die combat_die = init_combat_die();

    uint8_t zone_cards[7] = {0}; //7 indexes into the all_encounter_defs to define cards in the zone

    BoardState board = init_board();

    
}

void play_game(BoardState *board, int8_t num_players, char player_names[MAX_PLAYERS][NAME_LEN]) {
    


    start_game(num_players, player_names);
}

int8_t update_courage(BoardState *board, int8_t variance) {
    board->courage += variance;
    if (board->courage <= 0) {
        printf("The Fellowship's courage has faltered. The game is over, and Sauron has won.\n");
        return 1;
    }
    return 0;
}

int8_t update_nazgul(BoardState *board, int8_t variance) {
    board->nazghul_count += variance;
    if (board->nazghul_count >= NAZGHUL_MAX && !(board->flags & BF_EOWYNN)) {
        printf("The Nazgul have overwhelmed the Fellowship. The game is over and Sauron has won.\n");
        return 1;
    }
    return 0;
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
