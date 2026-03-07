#ifndef TOKENS_H
#define TOKENS_H

#include <stdint.h>

typedef struct {
    char initial;
    int8_t row, column, assisting, active;
}FellowshipToken;
enum {ARAGORN, GIMLI, LEGOLAS, MERRY_PIPPIN, FRODO_SAM};
FellowshipToken fellowship[5];

#endif
