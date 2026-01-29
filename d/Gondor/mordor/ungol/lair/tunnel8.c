/*
 * Tunnel8.c
 *
 * The entrance of Shelobs lair, Torech Ungol. In this room you will find a
 * gate. You can climb over this gate for there is no way to bolt/unbolt
 * this gate.
 *
 * /Mercade, 18 july 1993
 */

inherit "/d/Gondor/mordor/ungol/lair/std_lair";

#include "/d/Gondor/defs.h"

#define LAIR_GATE LAIR_DIR + "lairgate_west"

void
create_room()
{
    add_exit(LAIR_DIR + "tunnel7", "southwest", 0, 4);

    make_the_room();


    clone_object(LAIR_GATE)->move(TO);

}
