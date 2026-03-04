#ifndef DICE_H
#define DICE_H

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

#define DICE_SIDES 6 //all dice are D6

typedef enum {SIDE_U8, SIDE_STR} SideType;

typedef struct {
    //uint32_t die_color;
    size_t nsides;
    SideType side_type;
    const void *sides;
}Die;

extern uint8_t number_sides[DICE_SIDES];
extern const char *name_sides[DICE_SIDES];

extern const Die combat_die;
extern const Die standard_die;

extern int8_t rolls[5];

void roll_dice(int8_t count, int8_t rolls[]);

#endif
