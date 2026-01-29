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

#define EAST        "m25"
#define SE          "m26"
#define NW          "f30"

object guard;

void
create_dunlending()
{
    set_short("A meadow in Anorien");
    set_long("You stand in a small open meadow in the foothills of the "
        + "White Mountains. Lush grass grows here, despite the cold wind "
        + "that gusts down from the mountains. "
        + "@@extra_line@@" + "To the north is an ancient pine forest, "
        + "with massive trees and a variety of wildlife.\n");
    add_meadow_forest("north");
    add_item( ({"mountain", "mountains", "white mountain", "white mountains"}),
         "The White mountains seem like giants looking down at you. Rugged "
         + "and steep, they look impassable here.\n");

    add_item( ({"foothill", "foothills"}), "The foothills look almost like "
        + "the mountains before the mountains. They are steep, but still "
        + "forested.\n");

    add_exit(CAMP_ROOM_DIR + EAST, "east");
    add_exit(CAMP_ROOM_DIR + NW, "northwest");
    add_exit(CAMP_ROOM_DIR + SE, "southeast");

    add_meadow();
    meadow_herbs_2();
    if(!random(3))
    {
        TO->add_prop(TENT, 1);
        enter_tent("m24t");
    }
    add_guard_down();
}

void
reset_room()
{
    set_searched(0);
}
