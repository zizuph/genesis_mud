/*
 * File:    path1.c
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
    set_long("The forest opens to the north, and the path follows its "
        + "way towards a small mountain, the top of which appears "
        + "to be a plateau on which a large structure stands. South, the "
        + "path leads deeper into the warm, beautiful forest from "
        + "where the rich scent of earth and flowers waft softly.\n");
    add_item(({"structure","large structure"}),
        " It blends so well with the stone of the plateau "
        + "that is it difficult to discern any details from "
        + "this distance.\n");
    add_prop(ROOM_I_INSIDE, 0); // this is an outside room

    // where, command
    add_exit("/d/Genesis/start/human/wild2/forest1", "south"); // link to Genesis wild2
    add_exit("path2", "north");

    // when we come from DIRECTION, we see MESSAGE
    ENTRANCE_MSG("north", "You descend the steep, rocky mountain path.\n");
}

