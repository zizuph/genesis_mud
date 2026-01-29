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

#define SOUTH    "m21"
#define EAST    "f18"
#define WEST    "m15"
#define SE        "f19"
#define SW        "m20"
#define NW        "m12"
#define NE        "f16"


object guard;

void
create_dunlending()
{
    set_short("A meadow next to a forest in Anorien");
    set_long("A forest of old growth pine trees blocks your view to the "
        + "east. The trees are large enough that you could live up in their "
        + "branches, if only you could climb that high. Even the lowest "
        + "branches are far over your head. To the west, a meadow of rich "
        + "green grass grows, lush with skunk cabbage and herbs. "
        + "@@extra_line@@" + "\n");
    add_meadow_forest("northeast and southeast");
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
    set_no_exit_msg( ({"north"}),
        "You try to walk north but lose your footing.\n");

    add_exit(CAMP_ROOM_DIR + SOUTH, "south");
    add_exit(CAMP_ROOM_DIR + EAST, "east");
    add_exit(CAMP_ROOM_DIR + WEST, "west");
    add_exit(CAMP_ROOM_DIR + NE, "northeast");
    add_exit(CAMP_ROOM_DIR + NW, "northwest", 0, 0, 1);
    add_exit(CAMP_ROOM_DIR + SW, "southwest", 0, 0, 1);
    add_exit(CAMP_ROOM_DIR + SE, "southeast");

    add_meadow();
    meadow_herbs_2();
    if(!random(3))
    {
        TO->add_prop(TENT, 1);
        enter_tent("m16t");
    }
    add_guard_down();
}

void
reset_room()
{
    set_searched(0);
}
