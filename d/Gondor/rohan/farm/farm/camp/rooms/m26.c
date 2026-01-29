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

#define NW          "m24"
#define NE          "m25"


object guard;

void
create_dunlending()
{
    set_short("South end of small meadow");
    set_long("You find yourself on the south end of a small meadow. You are high "
        + "up in the foothills of the White Mountains. Try as you might, there "
        + "is no pass through the mountains here. The meadow itself is grassy "
        + "and full of beautiful wildflowers. "
        + "@@extra_line@@" + "\n");

    add_item( ({"mountain", "mountains", "white mountain", "white mountains"}),
         "The White mountains seem like giants looking down at you. Rugged "
         + "and steep, they look impassable here.\n");

    add_item( ({"foothill", "foothills"}), "The foothills look almost like "
        + "the mountains before the mountains. They are steep, but still "
        + "forested.\n");

    add_exit(CAMP_ROOM_DIR + NE, "northeast");
    add_exit(CAMP_ROOM_DIR + NW, "northwest");

    add_meadow();
    meadow_herbs_2();
    if(!random(3))
    {
        TO->add_prop(TENT, 1);
        enter_tent("m26t");
    }
    add_guard_down();
}

void
reset_room()
{
    set_searched(0);
}
