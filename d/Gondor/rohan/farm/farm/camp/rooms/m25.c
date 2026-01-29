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

#define WEST        "m24"
#define SW          "m26"
#define NE          "f31"

object guard;

void
create_dunlending()
{
    set_short("A small meadow in the foothills");
    set_long("This meadow is small, especially when compared to the massive "
        + "open meadow to through the forest to the north. However, looking at "
        + "the ground, you see signs of both humans and animals passing through. "
        + "@@extra_line@@" + "There are many wildflowers here, and some skunk "
        + "cabbage as well.\n");
    add_meadow_forest("north");
    add_item( ({"mountain", "mountains", "white mountain", "white mountains"}),
         "The White mountains seem like giants looking down at you. Rugged "
         + "and steep, they look impassable here.\n");

    add_item( ({"foothill", "foothills"}), "The foothills look almost like "
        + "the mountains before the mountains. They are steep, but still "
        + "forested.\n");
    add_item( ({"ground", "sign", "signs", "track", "tracks"}),
        "@@look_ground@@");

    add_exit(CAMP_ROOM_DIR + WEST, "west");
    add_exit(CAMP_ROOM_DIR + NE, "northeast");
    add_exit(CAMP_ROOM_DIR + SW, "southwest");

    add_meadow();
    meadow_herbs_2();
    if(!random(3))
    {
        TO->add_prop(TENT, 1);
        enter_tent("m25t");
    }
    add_guard_down();
}

void
reset_room()
{
    set_searched(0);


}

string
look_ground()
{
    say(QCTNAME(TP) + " squats down and looks closely at the ground.\n");
    return("Looking at the ground, you tracks. There are some deer and "
        + "wolf tracks, but also bootprints. The boots seem to be large, "
        + "heavy boots, like a soldier would wear, not at all typical for "
        + "a woodsman.\n");
}
