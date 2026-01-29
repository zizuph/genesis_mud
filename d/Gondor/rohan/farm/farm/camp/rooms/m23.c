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

#define NORTH       "f24"
#define NW          "f23"


object guard;

void
create_dunlending()
{
    set_short("An isolated meadow in Anorien");
    set_long("You are in the shadow of the White Mountains. While they are "
        + "still quite some distance away, you have to crane your neck to "
        + "see the tops of them. This meadow is noticeably cooler than the "
        + "large meadow through the forest to the north, due to the icy "
        + "wind that howls down from the mountains. "
        + "@@extra_line@@" + "Still, grass and wildflowers grow in "
        + "abundance here.\n");
    add_meadow_forest("north");
    add_item( ({"mountain", "mountains", "white mountain", "white mountains"}),
         "The White mountains seem like giants looking down at you. Rugged "
         + "and steep, they look impassable here.\n");

    add_item( ({"foothill", "foothills"}), "The foothills look almost like "
        + "the mountains before the mountains. They are steep, but still "
        + "forested.\n");

    add_exit(CAMP_ROOM_DIR + NORTH, "north");
    add_exit(CAMP_ROOM_DIR + NW, "northwest");

    add_meadow();
    meadow_herbs_3();
    if(!random(3))
    {
        TO->add_prop(TENT, 1);
        enter_tent("m23t");
    }

    add_guard_down();
}

void
reset_room()
{
    set_searched(0);
}
