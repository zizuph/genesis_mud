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

#define NORTH    "m16"
#define SOUTH    "f26"
#define EAST    "f19"
#define WEST    "m20"
#define SE      "f27"
#define SW      "f25"
#define NW      "m15"
#define NE


object guard;

void
create_dunlending()
{
    set_short("In a meadow north of the foothills");
    set_long("From here, you have dramatic views of the White Mountains, "
        + "their snow-capped peaks rising above the pines. To the northwest, "
        + "as far as you can see is a meadow, home to all sorts of life, "
        + "from bees to deer to humans. "
        + "@@extra_line@@" + "The wind carries the smell of campfires "
        + "across the meadow.\n");
    add_meadow_forest("south and east");
    add_item( ({"mountain", "mountains", "white mountain", "white mountains"}),
         "The White mountains look rugged and steep. They seem close, but "
        + "that's jus an illusion because of their size. In reality it would "
        + "take a day or two to walk to them--a day or two without any "
        + "trouble from Dunlendings or orcs.\n");
    add_item("herbs", "There are herbs growing here, but you'd have to take a "
        + "closer look to see which ones.\n");
    add_item( ({"branch", "branches"}), "The tree branches are thick around, "
        + "like a gnome's head. Even the lowest branches are way way up in the "
        + "tree, further than you could throw a rope to.\n");
    add_item( ({"boulder", "boulders"}), "The boulders look to be a white-"
        + "grey. They're very, very large, and even with an oliphant you "
        + "couldn't drag them away.\n");
    add_item( ({"foothill", "foothills"}), "The foothills look almost like "
        + "the mountains before the mountains. They are steep, but still "
        + "forested.\n");
    add_item( ({"bee", "bees"}), "You see the occasional flash of yellow, "
        + "as bees flit from flower to flower, gathering necter.\n");
    add_item( ({"needles", "pine needles"}), "You see pine needles "
        + "covering the ground in the forest. Sometimes, white-grey boulders "
        + "poke through them.\n");

    add_room_tell("You hear bees buzz.");
    add_room_tell("You see a bee land on a wildflower.");

    add_exit(CAMP_ROOM_DIR + NORTH, "north");
    add_exit(CAMP_ROOM_DIR + SOUTH, "south");
    add_exit(CAMP_ROOM_DIR + EAST, "east");
    add_exit(CAMP_ROOM_DIR + WEST, "west");
    add_exit(CAMP_ROOM_DIR + NW, "northwest", 0, 0, 1);
    add_exit(CAMP_ROOM_DIR + SW, "southwest", 0, 0, 1);
    add_exit(CAMP_ROOM_DIR + SE, "southeast", 0, 0, 1);

    add_meadow();
    meadow_herbs_2();
    if(!random(3))
    {
        TO->add_prop(TENT, 1);
        enter_tent("m21t");
    }
    add_guard_down();
}

void
reset_room()
{
    set_searched(0);
}
