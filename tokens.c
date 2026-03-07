#include "tokens.h"

/*
---------- Gonna be a lot of these ----------
           Token for each fellowship member
           Gandalf and Treebeard
           Uruk Hai and Nazghul      
---------- I'm not sure these need to exist for the REPL version----------      
*/
FellowshipToken fellowship[5] = {
    {.initial = 'G', .row = 0, .column = 0, .assisting = 1, .active = 1},
    {.initial = 'A', .row = 0, .column = 0, .assisting = 1, .active = 1},
    {.initial = 'L', .row = 0, .column = 0, .assisting = 1, .active = 1},
    {.initial = 'M', .row = 0, .column = 0, .assisting = 1, .active = 1},
    {.initial = 'F', .row = 0, .column = 0, .assisting = 0, .active = 1}
};
