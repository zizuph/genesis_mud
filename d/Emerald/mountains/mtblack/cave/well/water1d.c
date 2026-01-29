/* This code is adapted from the well in the Terel mansion. Many thanks to */
/* Dust for making such a fine job of it. Tulix, 24/6/1993 */

#define UP_ROOM        CAVE_DIR + "levelc/cave16c"
#define DOWN_ROOM      THIS_DIR + "water6e"

#define CREATEADD \
    add_exit(THIS_DIR + "water2d", "east", "@@try_hor"); \
    add_exit(THIS_DIR + "water4d", "north", "@@try_hor"); \
    add_exit(THIS_DIR + "water6e", "down", "@@try_down"); \
    add_exit(CAVE_DIR + "levelc/cave16c", "up", "@@try_up");

#include "Dive.h"
