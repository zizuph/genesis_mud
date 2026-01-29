/*
 * File:    lawn_west2.c
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
    set_short("between the monastery and the western edge of the plateau");
    set_long("The wall to the east is low here, topped with a wide slabs "
        + "of smooth shale. The grass underfoot is soft and slightly damp "
        + "with dew captured from the sheltered wind. To the southeast, "
        + "the lawn opens up into a wide area south of the monastery. "
        + living_view("lawn_nw", " Standing on the lawn to the "
        + "north, you see ", ".", "") + "\n");
    add_item(({"monastery","building"}),
        "Its ancient stones rise high overhead.\n");
    add_item(({"cliff","drop","down"}),
        "The sheer edge of the cliff drops down to a dark "
        + "forest below.\n");
    add_item(({"stone","stones"}),
        "The monastery is formed of enormous blocks of dark "
        + "grey stone.\n");
    add_prop(ROOM_I_INSIDE, 0); // this is an outside room

    // where, command
    add_exit("lawn_south", "southeast");
    add_exit("lawn_west1", "north");

}

