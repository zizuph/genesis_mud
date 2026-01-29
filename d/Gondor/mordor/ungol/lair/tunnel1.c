/*
 * /d/Gondor/mordur/ungol/lair/tunnel1.c
 *
 * The entrance of Shelobs lair, Torech Ungol.
 *
 * /Mercade, 18 july 1993
 *
 * Revision history:
 */

inherit "/d/Gondor/mordor/ungol/lair/std_lair";

#include "/d/Gondor/defs.h"

void
create_room()
{
    add_exit(STAIRS_DIR + "ravine3", "west", 0, 5);
    add_exit(LAIR_DIR +   "tunnel2",   "east", 0, 4);

    make_the_room(" From the west you feel a cool breeze. You guess there " +
        "is an exit in that direction.");
}
