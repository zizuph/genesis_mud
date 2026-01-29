/*
 * File:    path4.c
 * Creator: Cirion, 1998.12.04
 * Purpose: Mountain path leading up to the monastery
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
    set_short("rocky mountain path");
    set_long("The air is cold and moved by slow, strong wind here. The "
        + "path narrows and grows steeper to the north as it hugs "
        + "the face of the steep cliff, and descends in "
        + "a gentler slope to the south. Black-green treetops sway "
        + "gently below, their movements peaceful and harmonious. The "
        + "smell of pine and flowers hangs faintly in the air.\n");
    add_item(({"rock","rocks","pebble","pebbles","ground"}),
        "The rocks and pebbles underfoot make walking here "
        + "precarious.\n");
    add_item(({"forest","trees"}),
        "The forest below is a dark canopy the spreads out "
        + "as far as the eye can see.\n");
    add_item(({"trail","path"}),
        " It rises to the north and goes south into the "
        + "forest.\n");
    add_prop(ROOM_I_INSIDE, 0); // this is an outside room

    // where, command
    add_exit("path3", "south");
    add_exit("path5", "north");

    // when we come from DIRECTION, we see MESSAGE
    ENTRANCE_MSG("south", "You climb the steep, rocky path.\n");
    ENTRANCE_MSG("north", "You descend the steep, rocky mountain path.\n");

}

