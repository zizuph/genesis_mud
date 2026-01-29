/* This code is adapted from the well in the Terel mansion. Many thanks to */
/* Dust for making such a fine job of it. Tulix, 24/6/1993 */

#define UP_ROOM        CAVE_DIR + "cave1d"

#define CREATEADD \
    add_exit(THIS_DIR + "water8e", "south", "@@try_hor"); \
    add_exit(CAVE_DIR + "leveld/cave1d", "up", "@@try_up"); \
    add_exit(THIS_DIR + "water11e", "northwest", "@@try_hor");

#include "Dive.h"
