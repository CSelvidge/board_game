#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "board.h"
#include "tokens.h"

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
    BF_BOROMIR = 1u << 3, // Boromir is a unique card not attached to any zone that allows you to reroll one defeat against a uruk hai
    BF_HARDCORE = 1u << 4 // Is the Game set to hardcore
}BoardFlags;

typedef enum {
    MT_BOARD,
    MT_ROLL
}MoveType;

typedef struct {
    Zone current_zone;
    Destination destination;
    int8_t courage, uruk_hai_count, nazghul_count;
    uint8_t flags;
    int8_t frodo_advance;
} BoardState;

typedef struct {
    BoardState board;
    FellowshipToken fellowship[5];
}GameState;


#endif

