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

#define EAST    "m7"
#define SE        "m9"
#define SW        "m8"
#define NE        "m3"


object guard;

void
create_dunlending()
{
    set_short("In a meadow, near a forest");
    set_long("Tall grass extends in every direction, as you stand in the "
        + "meadow. " + "@@extra_line@@" + "From time to time you see "
        + "campfire smoke, and so you know you're not alone here. Somewhere "
        + "nearby, people are living.\n");
    add_item( "undergrowth", "Thick, overgrown clumps of bushes make up "
        + "the undergrowth. It looks like you couldn't possibly walk "
        + "through it.\n");

    add_exit(CAMP_ROOM_DIR + EAST, "east");
    add_exit(CAMP_ROOM_DIR + NE, "northeast");
    add_exit(CAMP_ROOM_DIR + SW, "southwest");
    add_exit(CAMP_ROOM_DIR + SE, "southeast");

    add_room_tell("You hear birds singing.");

    set_no_exit_msg( ({"south"}), "You have difficulty gaining any traction "
        + "heading south.\n");
    set_no_exit_msg( ({"north", "west", "northwest"}), "Thick undergrowth makes "
        + "impossible to walk in that direction.\n");

    add_meadow();
    meadow_herbs_1();
    if(!random(3))
    {
        TO->add_prop(TENT, 1);
    enter_tent("m6t");
    }

    add_guard_down();
}

void
reset_room()
{
    set_searched(0);
}
