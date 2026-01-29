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

#define NORTH       "f22"
#define NW          "f21"


object guard;

void
create_dunlending()
{
    set_short("A meadow in Anorien");
    set_long("Through the trees, you have dramatic views of the Forest and "
        + "meadow below. You find yourself in a small meadow sandwiched "
        + "between an ancient pine forest and the White Mountains. "
        + "@@extra_line@@" + "The wind blows crisp and cold down from the "
        + "mountains here, carrying with it the threat of snow.\n");
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
    meadow_herbs_2();
    if(!random(3))
    {
        TO->add_prop(TENT, 1);
        enter_tent("m22t");
    }

    add_guard_down();
}

void
reset_room()
{
    set_searched(0);
}
