/*
 * File:    lawn_east2.c
 * Creator: Cirion, 1998.12.04
 * Purpose: Area outside the monastery
 */
#pragma strict_types
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
    set_long("Furious and unrestrained, the bitter easterly wind "
        + "buffets the craggy western wall of the high monastery. The "
        + "grassy path is very narrow here, between the wall and the "
        + "edge of the plateau, which drops off the sheer edge "
        + "to the dizzying depths below. The grass covering the "
        + "ground is well-trod and lifeless.\n");
    add_item(({"monastery","building"}),
        "Its ancient stones rise high overhead.\n");
    add_item(({"cliff","drop","down"}),
        "The sheer edge of the cliff drops down to a dark "
        + "forest below.\n");
    add_item(({"stone","stones","wall","craggy wall","western wall"}),
        "The monastery is formed of enormous blocks of dark "
        + "grey stone.\n");
    add_item(({"grass","lawn","ground"}),
        "The grass is crushed down, dying, as if by the "
        + "passage of many feet along this way.\n");

    add_prop(ROOM_I_INSIDE, 0); // this is an outside room

    // where, command
    add_exit("lawn_south", "southwest");
    add_exit("lawn_east1", "north");

}

