/*
 * File:    path7.c
 * Creator: Cirion, 1998.12.04
 * Purpose: Mountain path leading up to the monastery
 */
#pragma strict_types

// since this is a guild room, save the binary of the file
// to facilitate quick loading after reboots
#pragma save_binary

#include "defs.h"
#include <tasks.h>

inherit ROOMBASE;

void
create_room ()
{
    set_short("rocky mountain path");
    set_long("A narrow, rocky path underfoot winds its precarious way "
        + "down around the cliff face to the west. "
        + "Tiny pebbles scatter over the edge "
        + "at every movement, floating like feathers down to the misty "
        + "forest below, which spreads out to the north as far as the "
        + "eye can see. South lies a grassy, windswept lawn leading "
        + "up to a large, rough-stone monastery.\n");
    add_item(({"rock","rocks","pebble","pebbles","ground"}),
        "The rocks and pebbles underfoot make walking here "
        + "precarious.\n");
    add_item(({"forest","trees"}),
        "The forest below is a dark canopy the spreads out "
        + "as far as the eye can see.\n");
    add_item(({"lawn","grass","south"}),
        "To the south, the top of the plateau is carpeted "
        + "by verdant grass that shivers with the wind and "
        + "leads to the great open doorway of a monastery.\n");
    add_item(({"monastery","rough-stone monastery"}),
        "It blends so well with the stone of the plateau "
        + "that even this near it is difficult to discern "
        + "details about it.\n");
    add_prop(ROOM_I_INSIDE, 0); // this is an outside room

    // where, command
    add_exit("lawn_ne", "south");
    add_exit("path6", "west");

    // when we come from DIRECTION, we see MESSAGE
    ENTRANCE_MSG("west", "You climb the steep, rocky path.\n");
    ENTRANCE_MSG("south", "You walk past the edge of the lawn and onto "
        + "the steep path descending down the side of the plateau.\n");
}

