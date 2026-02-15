#include <stdint.h>
#include <stddef.h>

#define DICE_SIDES 6 //all dice are D6

uint8_t number_sides[] = {1, 2, 3, 4, 5, 6};
const char* name_sides[] = {'Aragorn', 'Legolas', 'Gimli', 'Marry and Pippen', 'Sauron', 'Gandalf'};

typedef enum {SIDE_U8, SIDE_STR} SideType;

typedef struct {
    //uint32_t die_color;
    size_t nsides;
    SideType side_type;
    const void *sides;
}Die;

Die init_standard_die();
Die init_combat_die();
void roll_dice(Die dice[], uint8_t count, uint8_t rolls[]);
