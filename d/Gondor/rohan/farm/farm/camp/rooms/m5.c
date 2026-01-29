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

#define NORTH    "f7"
#define EAST    "f10"
#define WEST    "m4"
#define SE        "f12"
#define SW        "f11"
#define NW        "m2"
#define NE        "f8"


object guard;

void
create_dunlending()
{
    set_short("In a meadow, near a forest");
    set_long("You stand on the edge of the meadow, with the forest "
        + "encroaching eastward." + "@@extra_line@@" + " Tall grasses "
        + "and wildflowers provide both food and cover for animals "
        + "that live in the forest. Some of the grass has been "
        + "trampled down around here.\n");
    add_item( ({"grass", "ground", "trampled grass"}), "Several areas "
        + "of grass lie down unnaturally. With your tracking skills, "
        + "you infer people have been walking here, carlessly, not "
        + "worried about who finds the sign of their passing.\n");

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
    add_meadow_forest("east");
    add_meadow();
    meadow_herbs_3();
    if(!random(3))
    {
        TO->add_prop(TENT, 1);
        enter_tent("m5t");
    }

    add_guard_down();
}

void
reset_room()
{
    set_searched(0);
}
