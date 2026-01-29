/*
 * monk_occtrain2.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/* Ged */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

void
create_room()
{
    set_short("training room");
    set_long("This is a very small room. There is only one thing drawing your attention " +
             "in here, the master of unarmed combat.\n");

    INSIDE;
    add_prop(ROOM_M_NO_ATTACK,
             "You can not do that while on Sacred ground.\n");

    add_exit("monk_occtrain1", "west");
}
