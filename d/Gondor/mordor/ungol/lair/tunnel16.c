/*
 * Tunnel16.c
 *
 * The entrance of Shelobs lair, Torech Ungol. In this room you may find the
 * entrance to the tower. Just open the undergate
 *
 * /Mercade, 18 july 1993
 */

inherit "/d/Gondor/mordor/ungol/lair/std_lair";

#include "/d/Gondor/defs.h"

#define UNDERGATE MORDOR_DIR + "obj/undergate_lair"

void
create_room()
{
    add_exit(LAIR_DIR + "tunnel15", "southwest", 0, 4);

    make_the_room();

    clone_object(UNDERGATE)->move(TO);
}
