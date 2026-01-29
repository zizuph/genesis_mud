/*
 * Dunlending Camp Outdoor Room
 *
 * --Raymundo, March 2020
 */

#pragma strict_types

inherit "/d/Gondor/rohan/farm/farm/camp/lib/base_room";

#include <macros.h>
#include "/d/Gondor/defs.h"
#include "defs.h"

#define NORTH    "f8"
#define WEST      "m5"
#define SW        "f12"
#define NW        "f7"
#define NE        "f9"


object guard;

void
create_dunlending()
{
    set_short("In a forest, by a cliff in Anorien");
    set_long("The forest ends abruptly here at the edge of a cliff. "
        + "The cliff itself is very steep and you doubt you could "
        + "climb it, even with a rope. Pine trees somehow grow "
        + "here, seeming to cling to the rocks themselves.\n");
    add_item( ({"rock", "rocks"}), "The rocks look more like huge granite "
        + "boulders than just rocks. Some of them hang out over the cliff "
        + "looking as if they might fall at any moment, and yet they are "
        + "sturdy. Impossibly, trees grow out of them, their roots reaching "
        + "down into cracks and crevices.\n");
    
    set_no_exit_msg( ({"southeast", "south", "east"}), 
        "You can't walk that way because you'd fall right off the cliff and "
            + "die!\n");
    
    add_cliff();
    
    add_exit(CAMP_ROOM_DIR + NORTH, "north");
    add_exit(CAMP_ROOM_DIR + WEST, "west");
    add_exit(CAMP_ROOM_DIR + NE, "northeast");
    add_exit(CAMP_ROOM_DIR + NW, "northwest", 0, 0, 1);
    add_exit(CAMP_ROOM_DIR + SW, "southwest");

    
    add_forest();
    forest_herbs_1();
    if(!random(3))
    {
    forest_climb("f10_up");
    }
add_guard_down();
}

void
reset_room()
{
    set_searched(0);
}



