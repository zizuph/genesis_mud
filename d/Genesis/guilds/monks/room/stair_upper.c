/*
 * File:    stair_upper
 * Creator: Cirion, 1998.06.14
 * Purpose: Second story landing of the stairwell in the monk's guild hall
 */
#pragma strict_types
#include "defs.h"

inherit ROOMBASE;

void
create_room ()
{
    set_short("stairwell landing");
    set_long("Stone steps worn with the passage of many "
        + "feet over the years leads upwards and downwards. "
        + "This square landing opens to the west into "
        + "a large hallway from which a cool breeze "
        + "flows.\n");
    add_item(({"steps","stone"}),
        "The stone steps are worn smooth by the passage of "
        + "many feet.\n");


    // where, command
    add_exit("stair_lower", "down");
    add_exit("stair_top", "up");
    add_exit("hall_upper_north", "west");

    // when we come from DIRECTION, we see MESSAGE
    ENTRANCE_MSG("up", "You descend the stairwell to the "
        + "second story landing.\n");
    ENTRANCE_MSG("down", "You walk up the circular stairwell and "
        + "arrive at the second story landing.\n");
    ENTRANCE_MSG("west", "You walk through the opening into "
        + "the cool confines of the stairwell landing.\n");
}

