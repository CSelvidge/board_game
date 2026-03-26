#include <time.h>
#include "game.h"

/*Main exclusively handles global states like rand seeding*/
int main(void) {
    srand(time(NULL));
    start_game();

    return 0;
}





