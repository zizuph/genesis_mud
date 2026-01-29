/* This code is adapted from the well in the Terel mansion. Many thanks to */
/* Dust for making such a fine job of it. Tulix, 24/6/1993 */

#define UP_ROOM        THIS_DIR + "water1d"
#define DOWN_ROOM      THIS_DIR + "water2f"

#define CREATEADD \
    add_exit(THIS_DIR + "water1d", "up", "@@try_up"); \
    add_exit(THIS_DIR + "water2f", "down", "@@try_down"); \
    add_exit(THIS_DIR + "water5e", "southwest", "@@try_hor");

#include "Dive.h"
