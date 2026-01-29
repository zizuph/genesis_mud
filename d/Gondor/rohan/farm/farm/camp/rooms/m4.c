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

#define NORTH    "m2"
#define EAST    "m5"
#define WEST    "m3"
#define SE        "f11"
#define SW        "m7"
#define NW        "m1"
#define NE        "f7"


object guard;

void
create_dunlending()
{
    set_short("In a large open meadow in Anorien");
    set_long("To the northeast and southeast, a large old-growth "
        + "forest looms tall, casting shadows over the meadow. "
        + "Everwhere else, you see a meadow with tall green grass "
        + "and colorful flowers. Birds flit about from the tall "
        + "tree branches, down to the meadow to eat a bug or two, "
        + "and back up again to safety. " + "@@extra_line@@" + "\n");
    add_item( ({"shadow", "shadows"}), "The trees are tall, and they "
        + "cast long shadows, both in sun- and moon-light.\n");

    add_exit(CAMP_ROOM_DIR + NORTH, "north");
    add_exit(CAMP_ROOM_DIR + EAST, "east");
    add_exit(CAMP_ROOM_DIR + WEST, "west");
    add_exit(CAMP_ROOM_DIR + NE, "northeast", 0, 0, 1);
    add_exit(CAMP_ROOM_DIR + NW, "northwest", 0,0,1);
    add_exit(CAMP_ROOM_DIR + SW, "southwest");
    add_exit(CAMP_ROOM_DIR + SE, "southeast", 0, 0, 1);

    add_room_tell("You hear birds singing.");

    set_no_exit_msg( ({"south"}), "You have difficulty gaining any traction "
        + "heading south.\n");
    add_meadow_forest("northeast and southeast");
    add_meadow();
    meadow_herbs_1();
    if(!random(3))
    {
        TO->add_prop(TENT, 1);
        enter_tent("m4t");
    }

    add_guard_down();
}

void
reset_room()
{
    set_searched(0);
}
