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

#define NORTH    "m13"
#define SOUTH    "f23"
#define EAST    "m19"
#define WEST    "m17"
#define SE        "f24"
#define SW        "f22"
#define NE        "m14"


object guard;

void
create_dunlending()
{
    set_short("A meadow next to the foothills of the White Mountains");
    set_long("You stand in a meadow, the last piece of reasonably flat "
        + "land before the foothills of the White Mountains begin to "
        + "the south. "
        + "@@extra_line@@" + "Tall grass and wildflowers grow throughout "
        + "the meadow. As a result, many animals make their homes here.\n");
    add_meadow_forest("south");
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
    set_no_exit_msg( ({"northwest"}),
        "You try to walk northwest, but you trip!\n");

    add_exit(CAMP_ROOM_DIR + NORTH, "north");
    add_exit(CAMP_ROOM_DIR + SOUTH, "south");
    add_exit(CAMP_ROOM_DIR + EAST, "east");
    add_exit(CAMP_ROOM_DIR + WEST, "west");
    add_exit(CAMP_ROOM_DIR + NE, "northeast", 0, 0, 1);
    add_exit(CAMP_ROOM_DIR + SW, "southwest", 0, 0, 1);
    add_exit(CAMP_ROOM_DIR + SE, "southeast", 0, 0, 1);

    add_meadow();
    meadow_herbs_3();
    if(!random(3))
    {
        TO->add_prop(TENT, 1);
        enter_tent("m18t");
    }
    add_guard_down();
}

void
reset_room()
{
    set_searched(0);
}
