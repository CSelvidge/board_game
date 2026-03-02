#include "game.h"
#include "board.h"
#include "dice.h"
#include "cards.h"

void start_game(int8_t num_players, int8_t hardcore,  char player_names[MAX_PLAYERS][NAME_LEN]) {
    BoardState board;
    init_board(&board);

    const char* fellowship_names[] = {"Aragorn", "Gimli", "Legolas", "Marry and Pippen", "Frodo and Samwise"};
    int8_t battle_helpers[4] = {1, 1, 1, 1}; //All members of the fellowship spawn in assistance of the ring bearer, this indexes with the combat die

    if (hardcore) { //If hardcore mode is enabled, we need to track which player owns which friend cards for combat purposes
        uint8_t player_friends[MAX_PLAYERS][9] = {0}; //9 friend cards is the max in the game, hardcore mode forces players to only use the friends THEY own
    } else {
        uint8_t global_friends[9] = {0};
    }

    /*
    | The following is initialized by this point:
    | BoardState board, all encounter cards (defs, vars, states), Gandalf cards (defs and state), friend card array, zone card array
    | Fellowship tokens
    | Fellowship movement dice, enocunter dice, and combat die
    */

    int8_t playing = 1;
    /*Game loop time!*/
    while (playing) {
        printf("Well we at least got this far");
        break;
    }

    play_again(hardcore);
}
/*
----------BITPACKING RETURN VALUE----------
*/
int8_t play_again(int8_t hardcore) {
    uint8_t active = 0;
    printf("Do you want to play again? (y/n): ");
    char confirmation = getchar();
    if (confirmation == 'y' || confirmation == 'Y') {
        active |= PLAY_AGAIN;
        printf("Are the same players playing again? (y/n): ");
        clear_buffer();
        confirmation = getchar();
        if (confirmation == 'y' || confirmation == 'Y') {
            active |= SAME_PLAYERS;
            clear_buffer();
        }
        char* hardcore_mode = hardcore == 0 ? "not" : "";
        printf("Do you want to swap the hardcore mode? You are currently %s set to hardcore. (y/n): ", hardcore_mode);
        clear_buffer();
        confirmation = getchar();
        if ((confirmation == 'y' || confirmation == 'Y') && !hardcore) {
            active |= TOGGLE_HARDCORE;
        }
    }
    clear_buffer();
    return active;
}

void clear_buffer() {
    char c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}
