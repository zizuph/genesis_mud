/* This code is adapted from the well in the Terel mansion. Many thanks to */
/* Dust for making such a fine job of it. Tulix, 24/6/1993 */

#define UP_ROOM        THIS_DIR + "water5d"

#define CREATEADD \
    add_exit(THIS_DIR + "water5d", "up", "@@try_up"); \
    add_exit(THIS_DIR + "water9e", "north", "@@try_hor");

#include "Dive.h"
