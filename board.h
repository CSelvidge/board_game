#include <stdint.h>
#include "cards.h"
#include "tokens.h"
#include "dice.h"

#define NAZGHUL_MAX 9
#define URUKHAI_MAX 6
#define ZONE_SIZE 7

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
} BoardState;

int8_t update_courage(BoardState *board, int8_t variance); 
int8_t update_nazgul(BoardState *board, int8_t variance);

/*
Also updates the Ring Token (proxied by X until tokens are defined) to the correct position for when art assets are added in future
*/

/*
*****PROJECT HAS NOT PROGRESSED TO THE POINT TOKENS ARE DEFINED******
Moves the correct fellowship token (proxied by X until tokens are defined) to the corrent spot on the current zone array and update which fellowship members can assist in combat
*/
void move_fellowship_token(int x, unsigned char zone_spaces[], unsigned char battle_helpers[]);


/*
*****PROJECT HAS NOT PROGRESSED TO THE POINT TOKENS ARE DEFINED******
Updates the current amount of nazghul or uruk-hai on the board
*/

/*
Update current zone by:
-Setting new destination
--Swapping current zone cards to the new zone
---Checking for special gandalf card usage
*/
void update_zone(BoardState *board, int8_t zone_cards[], EncounterCardDef encounter_Card_defs[]);

/*
Set the:
-Default destination
--Default Zone cards
--Default board state
*/
BoardState init_board();
