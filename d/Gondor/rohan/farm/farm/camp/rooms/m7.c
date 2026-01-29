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

#define SOUTH    "f13"
#define EAST    "f11"
#define WEST    "m6"
#define SE        "f14"
#define SW        "m9"
#define NW        "m3"
#define NE        "m4"


object guard;

void
create_dunlending()
{
    set_short("In a meadow, near a forest");
    set_long("You stand in a wide open meadow, near an ancient pine "
        + "forest. To the east and southeast, tall trees stand, their "
        + "branches swaying in the wind. The meadow continues westward, "
        + "sunny during the day and moon-bright at night. "
        + "@@extra_line@@" + "Looking closely at the grass, you notice "
        + "herbs growing alongside the wildflowers.\n");

    add_item( ({"herb", "herbs"}), "You see many different kinds of herbs "
        + "here, but it's hard to identify them without taking a closer "
        + "look.\n");
    add_item( ({"branch", "branches"}), "The branches are very high up in "
        + "the trees. This is truly an ancient forest to have such tall "
        + "straight trees.\n");

    add_exit(CAMP_ROOM_DIR + SOUTH, "south");
    add_exit(CAMP_ROOM_DIR + EAST, "east");
    add_exit(CAMP_ROOM_DIR + WEST, "west");
    add_exit(CAMP_ROOM_DIR + NE, "northeast");
    add_exit(CAMP_ROOM_DIR + NW, "northwest", 0,0,1);
    add_exit(CAMP_ROOM_DIR + SW, "southwest",0, 0, 1);
    add_exit(CAMP_ROOM_DIR + SE, "southeast", 0, 0, 1);

    add_room_tell("You hear something snarling in the grass.");
    add_meadow_forest("east and southeast");
    set_no_exit_msg( ({"north"}), "You have difficulty gaining any traction "
        + "heading north.\n");

    add_meadow();
    meadow_herbs_1();
    if(!random(3))
    {
        TO->add_prop(TENT, 1);
        enter_tent("m7t");
    }

    add_guard_down();
}

void
reset_room()
{
    set_searched(0);
}




