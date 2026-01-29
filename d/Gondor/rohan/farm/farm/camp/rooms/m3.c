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

#define EAST    "m4"
#define SE        "m7"
#define SW        "m6"
#define NE        "m1"


object guard;

void
create_dunlending()
{
    set_short("On the edge of a meadow in Anorien");
    set_long("Thick undergrowth makes an impenetrable wall to the west. "
        + "But for nearly as far as you can see, a wise open meadow "
        + "stretches in every direction. Tall green grass and occasional "
        + "wildflowers make the meadow a rich feeding ground for deer and "
        + "other forest creatures, as well as the animals that prey "
        + "on them."+ "@@extra_line@@" +"\n");

    add_item("undergrowth", "The undergrowth is a combination of thick "
        + "plants, many of them thorny, preventing you from walking to "
        + "the west.\n");

    add_exit(CAMP_ROOM_DIR + EAST, "east");
    add_exit(CAMP_ROOM_DIR + NE, "northeast");
    add_exit(CAMP_ROOM_DIR + SW, "southwest");
    add_exit(CAMP_ROOM_DIR + SE, "southeast", 0, 0, 1);

    set_no_exit_msg( ({"northwest", "west"}), "Thick undergrowth prevents you "
        + "from moving that direction.\n");
    add_meadow_forest("northeast");
    add_meadow();
    meadow_herbs_3();
    if(!random(3))
    {
        TO->add_prop(TENT, 1);
    enter_tent("m3t");
    }
    add_guard_down();
}

void
reset_room()
{
    set_searched(0);
}
