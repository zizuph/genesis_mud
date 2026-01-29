/*
 * Hiding5.c
 *
 * A deadend tunnel in Shelobs lair, Torech Ungol.
 *
 * Olorin, 2-nov-1993, copied and modifed from 
 * /Mercade, 18 july 1993
 */

inherit "/d/Gondor/mordor/ungol/lair/std_lair";

#include "/d/Gondor/defs.h"

void create_room()
{
    add_exit(MORGUL_DIR + "tunnel/deadend6", "southwest", -2, 4);

    make_the_room("");
}
