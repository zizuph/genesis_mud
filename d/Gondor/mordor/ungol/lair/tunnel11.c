/*
 * Tunnel11.c
 *
 * The entrance of Shelobs lair, Torech Ungol. In this room you will find a
 * gate. It is possible to climb over the door. From this side however, you
 * can bolt and unbolt the door.
 *
 * /Mercade, 18 july 1993
 */

inherit "/d/Gondor/mordor/ungol/lair/std_lair";

#include "/d/Gondor/defs.h"

#define LAIR_GATE LAIR_DIR + "lairgate_east"

void
create_room()
{
    add_exit(LAIR_DIR + "tunnel12", "northeast", 0, 4);

    make_the_room();

    clone_object(LAIR_GATE)->move(TO);
}
