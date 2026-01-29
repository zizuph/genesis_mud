/*
 * Deadend5.c
 *
 * The entrance of Shelobs lair, Torech Ungol.
 *
 * /Mercade, 18 july 1993
 */

inherit "/d/Gondor/mordor/ungol/lair/std_lair";
#include "/d/Gondor/defs.h"

void
create_room()
{
    add_exit(LAIR_DIR + "deadend4", "north", 0, 4);
    add_exit(LAIR_DIR + "tunnel5",  "south", 0, 4);

    make_the_room();
}
