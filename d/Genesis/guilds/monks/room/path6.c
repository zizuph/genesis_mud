/*
 * File:    path6.c
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
    set_long("Bending sharply here against the craggy cliff wall, the "
        + "path descends to the southwest and rises to the east, where "
        + "it seems to level off at the top of a plateau. The rocky path "
        + "underfoot is unstable and treacherous, and vicious cold "
        + "winds buffet it from the north.\n");
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
    add_exit("path5", "southwest");
    add_exit("path7", "east");

    // when we come from DIRECTION, we see MESSAGE
    ENTRANCE_MSG("southwest", "You climb the steep, rocky path.\n");
    ENTRANCE_MSG("east", "You descend the steep, rocky mountain path.\n");
}

