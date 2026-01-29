/*
 * File:    stair_top
 * Creator: Cirion, 1998.06.14
 * Purpose: Top of the stairwell in the monk's guild hall
 */
#pragma strict_types
#include "defs.h"

inherit ROOMBASE;

void
create_room ()
{
    set_short("stairwell");
    set_long("This is the top landing of the circular "
        + "stairwell. Worn stone steps descend into darkness. "
        + "An opening to the west leads into a small central "
        + "room.\n");
    add_item(({"steps","stone"}),
        "The stone steps are worn smooth by the passage of "
        + "many feet.\n");


    // where, command
    add_exit("stair_upper", "down");
    add_exit("hall_top", "west");

    // when we come from DIRECTION, we see MESSAGE
    ENTRANCE_MSG("down", "You walk up the gloomy stairwell "
        + "to the top landing.\n");
}

