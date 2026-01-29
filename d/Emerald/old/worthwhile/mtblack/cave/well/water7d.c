/* This code is adapted from the well in the Terel mansion. Many thanks to */
/* Dust for making such a fine job of it. Tulix, 24/6/1993 */

#define UP_ROOM        CAVE_DIR + "cave26c"

#define CREATEADD \
    add_exit(THIS_DIR + "water6d", "south", "@@try_hor"); \
    add_exit(CAVE_DIR + "levelc/cave26c", "up", "@@try_up");

#include "Dive.h"
