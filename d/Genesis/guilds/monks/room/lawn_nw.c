/*
 * File:    lawn_ne.c
 * Creator: Cirion, 1998.11.26
 * Purpose: Area outside the monastery
 */
#pragma strict_types

// since this is a guild room, save the binary of the file
// to facilitate quick loading after reboots
#pragma save_binary

#include "defs.h"

inherit ROOMBASE;

void
create_room ()
{
    set_short("northwest lawn");
    set_long("Furious gusts of cold, hard wind blow up over the "
        + "sheer edge of the plateau to the north and west. The "
        + "grass underfoot is neat and well-tended. To the southeast, "
        + "the massive stone monastery rises up from the earth, "
        + "an ancient edifice made from craggy stone. The wide lawn continues "
        + "to the east, and to the south it narrows between the high "
        + "stone wall and the edge of the cliff to the west."
        + living_view("lawn_ne", " Standing on the lawn to the "
        + "east, you see ", ".", "") + "\n");
    add_item(({"grass","lawn","blades"}),
        "The grass is well manicured here, and quivers as "
        + "the wind blows across it.\n");
    add_item(({"cliff","drop","down"}),
        "The sheer edge of the cliff drops down to a dark "
        + "forest below.\n");
    add_item(({"stone","stones"}),
        "The monastery is formed of enormous blocks of dark "
        + "grey stone.\n");
    add_prop(ROOM_I_INSIDE, 0); // this is an outside room

    // where, command
    add_exit("lawn_ne", "east");
    add_exit("lawn_west1", "south");

}

