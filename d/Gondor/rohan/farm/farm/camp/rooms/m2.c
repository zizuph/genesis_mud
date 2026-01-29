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

#define NORTH    "f4"
#define SOUTH    "m4"
#define EAST    "f7"
#define WEST    "m1"
#define SE        "m5"
#define NE        "f5"


object guard;

void
create_dunlending()
{
    set_short("In a meadow in Anorien");
    set_long("South of you is a wide-open meadow. You see smoke from "
        + "campfires rising here and there, indicating that somwhere "
        + "in this large meadow, men reside. To the northeast is an "
        + "ancient forest of tall pine trees."+ "@@extra_line@@"
        + " Flashes of movement indicate "
        + "that many animals call the forest home--and perhaps, yes, also "
        + "some people.\n");

    add_exit(CAMP_ROOM_DIR + NORTH, "north");
    add_exit(CAMP_ROOM_DIR + SOUTH, "south");
    add_exit(CAMP_ROOM_DIR + EAST, "east");
    add_exit(CAMP_ROOM_DIR + WEST, "west");
    add_exit(CAMP_ROOM_DIR + NE, "northeast", 0, 0, 1);
    add_exit(CAMP_ROOM_DIR + SE, "southeast", 0, 0, 1);

    add_meadow_forest("northeast");
    add_meadow();
    meadow_herbs_1();
    if(!random(3))
    {
        TO->add_prop(TENT, 1);
        enter_tent("m2t");
    }
    add_guard_down();
}

void
reset_room()
{
    set_searched(0);
}
