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

#define NORTH    "f6"
#define SOUTH    "f10"
#define EAST    "f9"
#define WEST    "f7"
#define SW        "m5"
#define NW        "f5"
#define NE


object guard;

void
create_dunlending()
{
    set_short("In a forest, near a meadow in Anorien");
    set_long("You stand in a pine forest near the White Mountains. "
        + "Pine needles are scattered across the ground, covering "
        + "grasses and herbs. There is more than enough space between "
        + "the trees to walk, except to the northeast and southeast where "
        + "thick undergrowth prevents travel. A meadow opens up to the "
        + "southwest.\n");

    add_item("soil", "The soil must be rich and fertile, with all the herbs "
        + "growing around here.\n");
    set_no_exit_msg( ({"northeast", "southeast"}), "Thick undergrowth prevents "
        + "you from walking that direction.\n");
    add_item("undergrowth", "The undergrowth is thick and dense, preventing you "
        + "from walking through it.\n");
    add_forest_meadow("southwest");

    add_exit(CAMP_ROOM_DIR + NORTH, "north");
    add_exit(CAMP_ROOM_DIR + SOUTH, "south");
    add_exit(CAMP_ROOM_DIR + EAST, "east");
    add_exit(CAMP_ROOM_DIR + WEST, "west");
    add_exit(CAMP_ROOM_DIR + NW, "northwest", 0,0,1);
    add_exit(CAMP_ROOM_DIR + SW, "southwest", 0,0,1);


    add_forest();
    forest_herbs_3();
    if(!random(3))
    {
        forest_climb("f8_up");
    }

    add_guard_down();
}

void
reset_room()
{
    set_searched(0);
}
