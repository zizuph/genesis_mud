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

#define EAST    "m2"
#define SE        "m4"
#define SW        "m3"
#define NW        "p3"
#define NE        "f4"


object guard;

void
create_dunlending()
{
    set_short("In a meadow in Anorien");
    set_long("To the northwest, a path snakes its way toward a farming "
        + "settlement, and, past that, Edoras itself. Meanwhile, to the "
        + "northeast is a large forest of pine trees. The trees are some "
        + "of the largest you've seen, their branches reaching high "
        + "overhead. " + "@@extra_line@@"
        + "All about you to the south and east is a large, open "
        + "meadow full of grass and wildflowers.\n");

    add_item("edoras", "Home to the Riders of Rohan, Edoras looks either "
        + "like a safe place to rest behind thick walls or a promissing "
        + "target for well-timed raid. It's all a matter of perspective.\n");
    add_item("path", "The path to the northwest is hardly distinguishable "
        + "from a deer trail. It's just a single track of dirt worn amongst "
        + "the grass after years and years of being walked on. It leads "
        + "toward a farming settlement, and ultimately to Edoras.\n");
    add_item( ({"farm", "farms", "settlement", "farming settlement"}),
         "Far in the distance are a few farms. You could probably raid "
        + "them if you needed more food than the forest could provide.\n");

    add_exit(CAMP_ROOM_DIR + EAST, "east");
    add_exit(CAMP_ROOM_DIR + NE, "northeast");
    add_exit(CAMP_ROOM_DIR + NW, "northwest");
    add_exit(CAMP_ROOM_DIR + SW, "southwest");
    add_exit(CAMP_ROOM_DIR + SE, "southeast", 0, 0, 1);

    add_meadow_forest("northeast");
    add_meadow();
    meadow_herbs_2();
    if(!random(3))
    {
        TO->add_prop(TENT, 1);
        enter_tent("m1t");
    }

    add_guard_down();
}

void
reset_room()
{
    set_searched(0);
}
