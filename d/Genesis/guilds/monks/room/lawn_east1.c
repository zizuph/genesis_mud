/*
 * File:    lawn_east1.c
 * Creator: Cirion, 1998.12.04
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
    set_short("eastern side of the monastery");
    set_long("The northeast corner of the monastery is circular, "
        + "and rises up the height of the structure. The edge of the "
        + "plateau to the east is sheer, and winding between it and "
        + "the western monastery wall is a narrow, well-trodden "
        + "path through the dying grass.\n");
    add_item(({"monastery","building"}),
        "Its ancient stones rise high overhead.\n");
    add_item(({"cliff","drop","down"}),
        "The sheer edge of the cliff drops down to a dark "
        + "forest below.\n");
    add_item(({"stone","stones"}),
        "The monastery is formed of enormous blocks of dark "
        + "grey stone.\n");
    add_item(({"grass","lawn","ground"}),
        "The grass is crushed down, dying, as if by the "
        + "passage of many feet along this way.\n");

    add_prop(ROOM_I_INSIDE, 0); // this is an outside room

    // where, command
    add_exit("lawn_ne", "northwest");
    add_exit("lawn_east2", "south");

}

