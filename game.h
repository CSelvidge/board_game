#include <stdio.h>
#include "board.h"
#include "cards.h"
#include "dice.h"
#include "tokens.h"

#define MAX_PLAYERS 4
#define NAME_LEN 32
#define NAZGHUL_MAX 9
#define URUKHAI_MAX 6


void clear_buffer();

void start_game(int8_t max_players, char player_names[MAX_PLAYERS][NAME_LEN]);
