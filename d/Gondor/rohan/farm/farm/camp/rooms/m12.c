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

#define TENT    "_a_tent_sits_here"

#define NORTH    "f13"
#define EAST    "f16"
#define WEST    "m11"
#define SE        "m16"
#define SW        "m15"
#define NW        "m9"
#define NE        "f14"


object guard;

void
create_dunlending()
{
    set_short("A meadow mext to a pine forest in Anorien");
    set_long("To the north and east, a massive pine forest grows, "
        + "its trees ancient and tall, big enough to build homes in. "
        + "To the west is a large meadow, full of grass and wildflowers."
        + "@@extra_line@@" + " There are signs that people are around, "
        + "such as the smoke from campfires that you spot from time to "
        + "time.\n");

    add_meadow_forest("north and east");
    set_no_exit_msg( ({"south"}), "You "
        + "cannot find a trail leading in that direction.\n");

    add_exit(CAMP_ROOM_DIR + NORTH, "north");
    add_exit(CAMP_ROOM_DIR + EAST, "east");
    add_exit(CAMP_ROOM_DIR + WEST, "west");
    add_exit(CAMP_ROOM_DIR + NE, "northeast", 0, 0, 1);
    add_exit(CAMP_ROOM_DIR + NW, "northwest", 0, 0, 1);
    add_exit(CAMP_ROOM_DIR + SW, "southwest");
    add_exit(CAMP_ROOM_DIR + SE, "southeast", 0, 0, 1);

    add_meadow();
    meadow_herbs_2();

    if(!random(3))
    {
        TO->add_prop(TENT, 1);
        enter_tent("m12t");
    }

    add_guard_down();
}

void
reset_room()
{
    set_searched(0);
}
