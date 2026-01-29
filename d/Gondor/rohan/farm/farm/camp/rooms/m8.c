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

#define SOUTH    "m10"
#define EAST    "m9"
#define SE        "m11"
#define NE        "m6"


object guard;

void
create_dunlending()
{
    set_short("In a meadow, near a forest");
    set_long("You are surrounded by a large forest meadow. Tall grass "
        + "moves in the wind like waves on a lake. At your feet, you see "
        + "herbs growing amongst the grass. "
        + "@@extra_line@@" + "Far to the south are the White "
        + "Mountains, their jagged peaks just poking above the "
        + "pine trees' branches.\n");

    add_item( ({"herb", "herbs"}), "You see many different kinds of herbs "
        + "here, but it's hard to identify them without taking a closer "
        + "look.\n");
    add_item( ({"branch", "branches"}), "The branches are very high up in "
        + "the trees. This is truly an ancient forest to have such tall "
        + "straight trees.\n");
    add_item( ({"mountain", "mountains", "white mountain", "white mountains"}),
        "The White Mountains look tall and imposing from here. Rumor has it "
        + "that trolls live in the deep crevices and caves of those "
        + "mountains.\n");

    set_no_exit_msg( ({"north", "west", "northwest", "southwest"}), "You "
        + "cannot find a trail leading in that direction.\n");

    add_exit(CAMP_ROOM_DIR + SOUTH, "south");
    add_exit(CAMP_ROOM_DIR + EAST, "east");
    add_exit(CAMP_ROOM_DIR + NE, "northeast");
    add_exit(CAMP_ROOM_DIR + SE, "southeast", 0, 0, 1);

    add_room_tell("You hear something snarling in the grass.");

    add_meadow();
    meadow_herbs_2();
    if(!random(3))
    {
        TO->add_prop(TENT, 1);
        enter_tent("m8t");
    }
    
    add_guard_down();
}

void
reset_room()
{
    set_searched(0);
}
