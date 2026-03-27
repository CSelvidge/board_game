#include "game.h"
#include "board.h"
#include "dice.h"
#include "cards.h"

#define SCREEN_WIDTH 120


void init_game_state(GameState *game) {
    memset(&game->move_cntx.board, 0, sizeof(BoardState));

    game->move_cntx.board.courage = 13;
    game->move_cntx.board.uruk_hai_count = 1;
    game->move_cntx.board.nazghul_count = 1;

    memset(game->card_cntx.gandalf_cards, 0, sizeof(game->card_cntx.gandalf_cards));
    update_zone_cards(&game->move_cntx.board, game->card_cntx.zone_cards);
    init_encounter_states(game->card_cntx.encounter_card_states);

    game->move_cntx.fellowship[ARAGORN] = (FellowshipToken){.initial = 'A', .row = 0, .column = 0, .active = 1, .assisting = 1};
    game->move_cntx.fellowship[GIMLI] = (FellowshipToken){.initial = 'G', .row = 0, .column = 0, .active = 1, .assisting = 1};
    game->move_cntx.fellowship[LEGOLAS] = (FellowshipToken){.initial = 'L', .row = 0, .column = 0, .active = 1, .assisting = 1};
    game->move_cntx.fellowship[MERRY_PIPPIN] = (FellowshipToken){.initial = 'P', .row = 0, .column = 0, .active = 1, .assisting = 1};
    game->move_cntx.fellowship[FRODO_SAM] = (FellowshipToken){.initial = 'F', .row = 0, .column = 0, .active = 1, .assisting = 1};

    game->num_players = 0;
    memset(game->player_names, 0, sizeof(game->player_names));

    game->turn_count = 0;
}

void start_game() {
    GameState game;
    init_game_state(&game);

    int8_t active = (PLAY_AGAIN | FRESH);
    int8_t hardcore = 0;
    
    const char* fellowship_names[] = {"Aragorn", "Gimli", "Legolas", "Marry and Pippen", "Frodo and Samwise"};

    shuffle_cards(game.card_cntx.zone_cards, ZONE_CARD_SIZE);
    shuffle_cards(game.card_cntx.gandalf_cards, GANDALF_LEN);


    /*This loop into switch dictates if the game should continue, be reset, or exit*/
    while (active) {
        if (active & PLAY_AGAIN){
            if ((active & FRESH) || !(active & SAME_PLAYERS)) {
                game.num_players = greeting();
                get_player_names(game.num_players, game.player_names);
            }
            if (active & FRESH) {
                hardcore = ask_hardcore();
            }else if (active & TOGGLE_HARDCORE) {
                hardcore = !hardcore;
            }
        }
        if (hardcore) game.move_cntx.board.flags |= BF_HARDCORE;
        play_game(&game);
        active = play_again(hardcore); //returns active as bitpacked
    }

}
/*
----------BITPACKING RETURN VALUE----------
*/

void play_game(GameState *game) {
    uint8_t playing = 1;
    while (playing) {
    draw_screen(game);
    game->turn_count++;
    playing = 0;
    }
}
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
/*
  Primary function to handle the REPL implimentation
  To make the function smaller, and easier to read and modify -
  It will handle much of the "calling" logic and allow subfunctions -
  to handle much of the actual drawing
*/
void draw_screen(GameState *game) {
    /*
      1) active_rows is a bitpacked byte which determines which rows need to be drawn, the ringbearers row is always active, others are only active if occupied
      2)draw_rows is only responsible for drawing the rows themselves on the center of the screen, and as such takes active rows as an argument

    */
   //Turn: # -- Destination: -- Gandalf & Treebeard?
    draw_top(game);
    uint8_t active_rows = calculate_rows(&game->move_cntx);
    draw_rows(active_rows, &game->move_cntx);

}

void draw_top(GameState *game) {
    //Yay boilerplate
    uint8_t buff_count = 0;

    char line_buff[SCREEN_WIDTH + 1];
    memset(line_buff, ' ', SCREEN_WIDTH);
    line_buff[SCREEN_WIDTH] = '\0';
    /*
      Turn count -> Destination -> something else
    */
    uint8_t len = snprintf(line_buff, 12, "Turn: %d ", game->turn_count);
    line_buff[len] = ' ';

    len = snprintf(line_buff + (SCREEN_WIDTH / 2), 28, "Destination: %s", destinations[game->move_cntx.board.destination]); //28 is from "Destination: " + destinations column length
    line_buff[(SCREEN_WIDTH / 2) + len] = ' ';

    printf("%s\n", line_buff);
}

uint8_t calculate_rows(MovementContext *move_cntx) {
    uint8_t active_rows = {0}; //Bitpacked bytes
    active_rows |= 1u << move_cntx->fellowship[FRODO_SAM].row;
    for (uint8_t i = 0; i < FELLOWSHIP_LENGTH - 1; i++) {
        if (move_cntx->fellowship[i].row != move_cntx->fellowship[FRODO_SAM].row) {
            active_rows |= (1u << move_cntx->fellowship[i].row);
        }
    }
    return active_rows;
}

void draw_rows(uint8_t active_rows, MovementContext *move_cntx) {
    uint8_t buff_count = 0;

    char line_buff[SCREEN_WIDTH + 1]; // + 1 for nully boi
    memset(line_buff, ' ', SCREEN_WIDTH);
    line_buff[SCREEN_WIDTH] = '\0';

    for (uint8_t i = 0; i < ZONE_COUNT; i++) {
        if (!(active_rows & 1u << i)) continue;
        memcpy(line_buff + (SCREEN_WIDTH / 2), zone_arrays[i], ZONE_SIZE); //Avoid extra loop work by flattening the loops and checking against already established charcters
        for (uint8_t j = 0; j < FELLOWSHIP_LENGTH; j++) {
            if (move_cntx->fellowship[j].row != i) continue;
            if (i == move_cntx->fellowship[FRODO_SAM].row){
                uint8_t len = snprintf(line_buff, 18, "Uruk-Hai count: %d", move_cntx->board.uruk_hai_count);
                line_buff[len] = ' '; //Remove null terminator or the string ends too early
                buff_count += len;
                uint8_t end_buff_pos = (SCREEN_WIDTH - strlen("Nazgul Count:  "));
                snprintf(line_buff + end_buff_pos, SCREEN_WIDTH - end_buff_pos + 1, "Nazgul count: %d", move_cntx->board.nazghul_count);
            }
            uint8_t token_pos = (SCREEN_WIDTH / 2) + move_cntx->fellowship[j].column;
            line_buff[token_pos] = move_cntx->fellowship[j].initial;
        }
        printf("%s\n", line_buff);
        memset(line_buff, ' ', SCREEN_WIDTH); //Reset line_buff to spaces once you have already drawn the current row to screen
    }
}
