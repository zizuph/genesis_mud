/* This code is adapted from the well in the Terel mansion. Many thanks to */
/* Dust for making such a fine job of it. Tulix, 24/6/1993 */

#define CREATEADD \
    add_exit(THIS_DIR + "water4d", "southeast", "@@try_hor"); \
    add_exit(THIS_DIR + "water7d", "north", "@@try_hor");

#include "Dive.h"
