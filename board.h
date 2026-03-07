#ifndef BOARD_H
#define BOARD_H

#include <stdint.h>
#include "cards.h"
#include "tokens.h"
#include "dice.h"

#define NAZGHUL_MAX 9
#define URUKHAI_MAX 6
#define ZONE_SIZE 9

extern const char zone_arrays[6][9];

typedef enum {
    ZONE_RIVENDELL,
    ZONE_LOTHLORIEN,
    ZONE_ROHAN,
    ZONE_HELMSDEEP,
    ZONE_GONDOR,
    ZONE_MINASMORGUL,
    ZONE_COUNT
} Zone;

typedef enum { // Start at rivendell so it isnt a destination
    LOTHLORIEN, //Since you start at rivendell this points to the current Zone at the same index although this feels one ahead
    ROHAN,
    HELMSDEEP,
    GONDOR,
    MINASMORGUL,
    MOUNTDOOM,
    DESTINATION_COUNT
} Destination;

typedef enum {
    BF_EOWYNN = 1u << 0, // If eowynn is successful the nazghul cannot end the game
    BF_GANDALF = 1u << 1, // If gandalf is in helms deep you cannot use gandalf cards
    BF_TREEBEARD = 1u << 2, // If treebeard is in play you can defeat the uruk hai cheiftan
    BF_BOROMIR = 1u << 3 // Boromir is a unique card not attached to any zone that allows you to reroll one defeat against a uruk hai
}BoardFlags;

typedef struct {
    Zone current_zone;
    Destination destination;
    int8_t courage, uruk_hai_count, nazghul_count;
    uint8_t flags;
    int8_t frodo_advance;
} BoardState;

BoardState init_board();

int8_t update_courage(BoardState *board, int8_t variance); 
int8_t update_nazgul(BoardState *board, int8_t variance);

void move_fellowship_token(FellowshipToken fellowship[5], int8_t index, BoardState *board, const char zone_arrays[6][9], int8_t variance);

void update_zone(BoardState *board, int8_t zone_cards[]);

#endif
