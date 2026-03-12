#include "game.h"
#include "board.h"
#include "dice.h"
#include "cards.h"


void init_game_state(GameState *game) {
    memset(&game->board, 0, sizeof(BoardState));

    game->board.courage = 13;
    game->board.uruk_hai_count = 1;
    game->board.nazghul_count = 1;

    game->fellowship[ARAGORN] = (FellowshipToken){.initial = 'A', .row = 0, .column = 0, .active = 1, .assisting = 1};
    game->fellowship[GIMLI] = (FellowshipToken){.initial = 'G', .row = 0, .column = 0, .active = 1, .assisting = 1};
    game->fellowship[LEGOLAS] = (FellowshipToken){.initial = 'L', .row = 0, .column = 0, .active = 1, .assisting = 1};
    game->fellowship[MERRY_PIPPIN] = (FellowshipToken){.initial = 'P', .row = 0, .column = 0, .active = 1, .assisting = 1};
    game->fellowship[FRODO_SAM] = (FellowshipToken){.initial = 'F', .row = 0, .column = 0, .active = 1, .assisting = 1};

}

void start_game(int8_t num_players, int8_t hardcore,  char player_names[MAX_PLAYERS][NAME_LEN]) {
    const char* fellowship_names[] = {"Aragorn", "Gimli", "Legolas", "Marry and Pippen", "Frodo and Samwise"};

    GameState game;
    init_game_state(&game);

    update_zone_cards(&game.board, zone_cards);
    shuffle_cards(zone_cards, ZONE_CARD_SIZE);
    shuffle_cards(gandalf_cards, GANDALF_LEN);
    if (!draw_gandalf_card(gandalf_cards)){
        printf("There are no more Gandlf Cards to draw.");
    }


    /*This if block doesn not "work", the scope is incorrect for the array declarations.
      But it serves as an easy to remember problem, and i can add logic to it here before i refine it to working solution
    */
    if (hardcore) { //If hardcore mode is enabled, we need to track which player owns which friend cards for combat purposes
        uint8_t player_friends[MAX_PLAYERS][9] = {0}; //9 friend cards is the max in the game, hardcore mode forces players to only use the friends THEY own
        game.board.flags |= BF_HARDCORE;
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
        for (int8_t i = 0; i < ZONE_COUNT; i++) {
            for (int8_t j = 0; j < ZONE_CARD_SIZE; j++){
                printf("%s\n", encounter_card_defs[zone_cards[j]].name);
            }
            printf("\n");
            game.board.current_zone++;
            update_zone_cards(&game.board, zone_cards);
            shuffle_cards(zone_cards, ZONE_CARD_SIZE);
        }
    printf("Size of one token: %zu\n", sizeof(FellowshipToken));
    printf("Size of token array: %zu\n", sizeof(game.fellowship));
    playing = 0;
    }
}
/*
----------BITPACKING RETURN VALUE----------
*/
int8_t play_again(int8_t hardcore) {
    int8_t active = 0;
    char confirmation[8] = {0};
    char message[128] = {0};

    get_user_input("Do you want to play again? (y/n): ", confirmation, sizeof(confirmation));
    if (confirmation[0] == 'y' || confirmation[0] == 'Y') {
        active |= PLAY_AGAIN;
        get_user_input("Are the same players playing again? (y/n): ", confirmation, sizeof(confirmation));
        if (confirmation[0] == 'y' || confirmation[0] == 'Y') {
            active |= SAME_PLAYERS;
        }
        char* hardcore_mode = hardcore == 0 ? "not " : "";
        snprintf(message, sizeof(message),
        "Do you want to swap the hardcore mode? You are currently %sset to hardcore. (y/n): ", hardcore_mode);
        get_user_input(message, confirmation, sizeof(confirmation));
        if (confirmation[0] == 'y' || confirmation[0] == 'Y') {
            active |= TOGGLE_HARDCORE;
        }
    }
    return active;
}

void get_user_input(const char *message, char *buffer, size_t return_size) {
    printf("%s", message);
    fgets(buffer, return_size, stdin);
    size_t newline_pos = strcspn(buffer, "\n");
    if (buffer[newline_pos] != '\n') {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {}
    }
    buffer[newline_pos] = '\0';
}

