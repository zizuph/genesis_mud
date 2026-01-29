/* This code is adapted from the well in the Terel mansion. Many thanks to */
/* Dust for making such a fine job of it. Tulix, 24/6/1993 */

#define UP_ROOM        THIS_DIR + "water6e"

#define CREATEADD \
    add_exit(THIS_DIR + "water1f", "south", "@@try_hor"); \
    add_exit(THIS_DIR + "water3f", "northeast", "@@try_hor"); \
    add_exit(THIS_DIR + "water6e", "up", "@@try_up");

#include "Dive.h"
