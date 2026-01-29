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

#define WEST    "f8"
#define SW        "f10"
#define NW        "f6"

object guard;

void
create_dunlending()
{
    set_short("In a forest, near a meadow in Anorien");
    set_long("In almost every direction, thick undergrowth hampers your "
        + "movement. You are deep in the forest here, and despite the "
        + "space between the pine trees, it feels dim. A few ferns grow "
        + "here and there, but mostly the ground is covered in pine "
        + "needles and pinecones.\n");

    add_item( ({"fern", "ferns"}), "The ferns are about knee-high to a human "
        + "and their leaves are very wide.\n");
    set_no_exit_msg( ({"northeast", "southeast", "north", "south", "east"}),
        "Thick undergrowth prevents "
        + "you from walking that direction.\n");
    add_item("undergrowth", "The undergrowth is thick and dense, preventing you "
        + "from walking through it.\n");
    add_pinecone();

    add_exit(CAMP_ROOM_DIR + WEST, "west");
    add_exit(CAMP_ROOM_DIR + NW, "northwest");
    add_exit(CAMP_ROOM_DIR + SW, "southwest");


    add_forest();
    forest_herbs_1();
    if(!random(3))
    {
        forest_climb("f9_up");
    }

    add_guard_down();
}

void
reset_room()
{
    set_searched(0);
}