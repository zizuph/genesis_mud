/*
 * Deadend6.c
 *
 * A deadend tunnel in Shelobs lair, Torech Ungol.
 *
 * Olorin, 30 oct 1993, copied and modifed from 
 * /Mercade, 18 july 1993
 */

inherit "/d/Gondor/mordor/ungol/lair/std_lair";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

int     ic = 0;

void create_room()
{
    add_exit(MORGUL_DIR + "tunnel/hiding5", "northeast", -2, 4);
    add_exit(LAIR_DIR + "deadend6", "southeast",  0, 4);
    add_exit(MORGUL_DIR + "tunnel/hiding3", "northwest", 0, 4);

    make_the_room("");
    ic++;
}

