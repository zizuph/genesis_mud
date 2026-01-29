/* This code is adapted from the well in the Terel mansion. Many thanks to */
/* Dust for making such a fine job of it. Tulix, 24/6/1993 */

#define DOWN_ROOM      THIS_DIR + "water7e"

#define CREATEADD \
    add_exit(THIS_DIR + "water3d", "south", "@@try_hor"); \
    add_exit(THIS_DIR + "water7e", "down", "@@try_down");

#include "Dive.h"
