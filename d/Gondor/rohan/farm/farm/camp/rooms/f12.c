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

#define NORTH    "f10"
#define WEST    "f11"
#define SW        "f15"
#define NW        "m5"
#define NE        "f10"


object guard;

void
create_dunlending()
{
    set_short("Next to a cliff in a forest in Anorien");
    set_long("You stand on a large granite shelf which hangs out over a steep "
        + "cliff. Trees still grow here, but they cling almost inexplicably "
        + "to the rock, with roots going down deep into the cracks. Far down "
        + "below you see the cliff end in a narrow ravine. It would not be a "
        + "good idea to climb down there, even with a rope.\n");
    add_item( ({"rock", "rocks", "shelf", "granite", "granite shelf"}),
        "The rocks look more like huge granite "
        + "boulders than just rocks. Some of them hang out over the cliff "
        + "looking as if they might fall at any moment, and yet they are "
        + "sturdy. Impossibly, trees grow out of them, their roots reaching "
        + "down into cracks and crevices.\n");

    set_no_exit_msg( ({"southeast", "south", "east"}),
        "You can't walk that way because you'd fall right off the cliff and "
            + "die!\n");

    add_cliff();

    add_exit(CAMP_ROOM_DIR + WEST, "west");
    add_exit(CAMP_ROOM_DIR + NE, "northeast");
    add_exit(CAMP_ROOM_DIR + NW, "northwest", 0, 0, 1);
    add_exit(CAMP_ROOM_DIR + SW, "southwest");


    add_forest();
    forest_herbs_2();
    if(!random(3))
    {
    forest_climb("f12_up");
    }
add_guard_down();
}

void
reset_room()
{
    set_searched(0);
}



