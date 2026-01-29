/*
 * File:    lawn_west1.c
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
    set_long("The soft grass underfoot makes precarious footing near "
        + "the western edge of the plateau, which drops down past "
        + "a narrow, rocky path to the vally below. To the east stands "
        + "the western wall of the monastery, made from craggy blocks "
        + "of rough-hewn stone. The wind here is buffered by the monastery "
        + "wall, making it less bitter than in the open lawn to the "
        + "north. The path here continues to the south."
        + living_view("lawn_nw", " Standing on the lawn to the "
        + "north, you see ", ".", "") + "\n");
    add_item(({"grass","lawn","blades"}),
        "The grass is long and soft here.\n");
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
    add_exit("lawn_nw", "north");
    add_exit("lawn_west2", "south");

}

