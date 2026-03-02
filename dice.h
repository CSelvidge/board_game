#include <stdint.h>
#include <stddef.h>

#define DICE_SIDES 6 //all dice are D6

uint8_t number_sides[] = {1, 2, 3, 4, 5, 6};

const Die combat_die;
const Die standard_die;

typedef enum {SIDE_U8, SIDE_STR} SideType;

typedef struct {
    //uint32_t die_color;
    size_t nsides;
    SideType side_type;
    const void *sides;
}Die;

void roll_dice(uint8_t count, uint8_t rolls[]);
