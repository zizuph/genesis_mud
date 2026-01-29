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

#define NORTH    "f15"
#define WEST    "f16"
#define SW        "f18"
#define NW        "f14"

object guard;

void
create_dunlending()
{
    set_short("Near a cliff in a forest");
    set_long("All you can see to the west are pine trees. The forest is "
        + "thick with them, and yet they grow wide enough apart that you "
        + "can walk easily between them. They shed pine needles, which "
        + "cover the forest floor like fur on a bear. "
        + "To the east, a large cliff leads down "
        + "into a ravine, stopping your progress.\n");


    set_no_exit_msg( ({"south", "east", "southeast", "northeast"}),
        "The cliff is too steep for you to proceed in that direction.\n");
    add_cliff();


    add_exit(CAMP_ROOM_DIR + NORTH, "north");
    add_exit(CAMP_ROOM_DIR + WEST, "west");
    add_exit(CAMP_ROOM_DIR + NW, "northwest", 0, 0, 1);
    add_exit(CAMP_ROOM_DIR + SW, "southwest", 0, 0, 1);


    add_forest();
    forest_herbs_1();
    if(!random(3))
    {
    forest_climb("f17_up");
    }
add_guard_down();
}

void
reset_room()
{
    set_searched(0);
}



