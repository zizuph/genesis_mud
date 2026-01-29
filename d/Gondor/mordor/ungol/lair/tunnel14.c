/*
 * Tunnel14.c
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
    add_exit(LAIR_DIR + "tunnel13", "southwest", 0, 4);
    add_exit(LAIR_DIR + "tunnel15", "east",      0, 4);

    make_the_room();
}
