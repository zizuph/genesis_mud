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

#define SOUTH    "f22"
#define EAST    "m18"
#define SE        "f23"
#define SW        "f21"
#define NE        "m13"

object guard;

void
create_dunlending()
{
    set_short("A meadow next to the foothills of the White Mountains");
    set_long("To your south, the forest rises steeply. The flatlands "
        + "end and the foothills begin. Large granite boulders begin to "
        + "show between the trees. The meadow extends east and northeast "
        + "from here, flat and calm compared to the geological drama of "
        + "the mountains. "
        + "@@extra_line@@" + "\n");
    add_meadow_forest("south");
    add_item( ({"mountain", "mountains", "white mountain", "white mountains"}),
         "The White mountains look rugged and steep. They seem close, but "
        + "that's just an illusion because of their size. In reality it would "
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
    set_no_exit_msg( ({"north", "west", "northwest"}),
        "You try to walk that way but lose your footing.\n");

    add_exit(CAMP_ROOM_DIR + SOUTH, "south");
    add_exit(CAMP_ROOM_DIR + EAST, "east");
    add_exit(CAMP_ROOM_DIR + NE, "northeast");
    add_exit(CAMP_ROOM_DIR + SW, "southwest");
    add_exit(CAMP_ROOM_DIR + SE, "southeast", 0, 0, 1);

    add_meadow();
    meadow_herbs_2();
    if(!random(3))
    {
        TO->add_prop(TENT, 1);
        enter_tent("m17t");
    }
    add_guard_down();
}

void
reset_room()
{
    set_searched(0);
}
