/*
 * File:    path2.c
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
    set_long("This wide, rocky trail meets with the face of mountain "
        + "on its east side and begins to ascend to the north, where "
        + "it rises far above the trees and to the top of what seems "
        + "to be a plateau. The breeze here is warm and carries the "
        + "scents of pine and edelweiss.\n");
    add_item(({"trail","path"}),
        " It rises to the north and goes south into the "
        + "forest.\n");
    add_prop(ROOM_I_INSIDE, 0); // this is an outside room

    // where, command
    add_exit("path1", "south");
    add_exit("path3", "north");

    // when we come from DIRECTION, we see MESSAGE
    ENTRANCE_MSG("south", "You climb the steep, rocky path.\n");
    ENTRANCE_MSG("north", "You descend the steep, rocky mountain path.\n");
}

