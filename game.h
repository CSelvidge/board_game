#include <stdio.h>
#include "board.h"
#include "cards.h"
#include "dice.h"
#include "tokens.h"

#define MAX_PLAYERS 4
#define NAME_LEN 32


void play_game(int8_t num_players, char player_names[MAX_PLAYERS][NAME_LEN]);
void clear_buffer();

int8_t play_again();
