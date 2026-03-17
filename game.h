#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <GLFW/glfw3.h>
#include "board.h"
#include "cards.h"
#include "dice.h"
#include "tokens.h"

#define MAX_PLAYERS 4
#define NAME_LEN 32

/*Bit fields for replaying the game*/
#define PLAY_AGAIN (1 << 0)
#define SAME_PLAYERS (1 << 1)
#define TOGGLE_HARDCORE (1 << 2)
#define FRESH (1 << 3)


typedef struct MovementContext{
    BoardState board;
    FellowshipToken fellowship[5];
}MovementContext;

typedef struct GameState {
    MovementContext move_cntx;
    uint8_t gandalf_cards[GANDALF_LEN];
    uint8_t zone_cards[ZONE_CARD_SIZE];
    EncounterCardState encounter_card_states[42];
}GameState;

extern const char* fellowship_names[];

void play_game(int8_t num_players, char player_names[MAX_PLAYERS][NAME_LEN]);
void get_user_input(const char *message, char *buffer, size_t return_size);
void init_game_state(GameState *game);
int8_t play_again(int8_t hardcore);

#endif
