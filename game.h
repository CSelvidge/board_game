#include <stdio.h>
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

void play_game(int8_t num_players, char player_names[MAX_PLAYERS][NAME_LEN]);
void clear_buffer();

int8_t play_again();
