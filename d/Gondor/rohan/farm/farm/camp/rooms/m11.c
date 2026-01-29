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

#define NORTH    "m9"
#define EAST    "m12"
#define WEST    "m10"
#define SE        "m15"
#define SW        "m14"
#define NW        "m8"
#define NE        "f13"


object guard;

void
create_dunlending()
{
    set_short("A meadow in Anorien");
    set_long("An open meadow extends in every direction, except to the "
        + "east, where an ancient pine forest grows. The trees in the "
        + "forest are some of the largest you've ever seen, with trunks "
        + "so thick you couln't get your arms to link around them. The "
        + "meadow is covered in thick grass, perfect for deer to eat "
        + "and grow fat on. "
        + "@@extra_line@@" + "\n");


    set_no_exit_msg( ({"south"}), "You "
        + "cannot find a trail leading in that direction.\n");

    add_exit(CAMP_ROOM_DIR + NORTH, "north");
    add_exit(CAMP_ROOM_DIR + EAST, "east");
    add_exit(CAMP_ROOM_DIR + WEST, "west");
    add_exit(CAMP_ROOM_DIR + NE, "northeast", 0, 0, 1);
    add_exit(CAMP_ROOM_DIR + NW, "northwest", 0, 0, 1);
    add_exit(CAMP_ROOM_DIR + SW, "southwest");
    add_exit(CAMP_ROOM_DIR + SE, "southeast", 0, 0, 1);

    add_meadow_forest("northeast");

    add_meadow();
    meadow_herbs_1();
    if(!random(3))
    {
        TO->add_prop(TENT, 1);
        enter_tent("m11t");
    }

    add_guard_down();
}

void
reset_room()
{
    set_searched(0);
}
