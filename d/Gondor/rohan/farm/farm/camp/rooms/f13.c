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

#define NORTH    "m7"
#define SOUTH    "m12"
#define EAST    "f14"
#define WEST    "m9"
#define SE        "f16"
#define SW        "m11"
#define NE        "f11"


object guard;

void
create_dunlending()
{
    set_short("Next to a meadow in a forest in Anorien");
    set_long("Grass and ferns pop up through the pine needles here, "
        + "nourished by the extra sunlight that reaches the ground "
        + "right next to the meadow. The trees are tall and straight, "
        + "with branches far out of reach. From time to time you "
        + "see a rabbit hop by, stealthily making its way into the "
        + "meadow to eat.\n");

    add_cmd_item("grass", ({"munch", "eat"}), "The rabbits eat the "
        + "grass, not you. Go to an inn or something!\n");
    set_no_exit_msg( ({"northwest"}),
        "Try as you might, you cannot find a trail leading northwest.\n");
    add_forest_meadow("north and south");
    add_pinecone();

    add_exit(CAMP_ROOM_DIR + NORTH, "north");
    add_exit(CAMP_ROOM_DIR + SOUTH, "south");
    add_exit(CAMP_ROOM_DIR + EAST, "east");
    add_exit(CAMP_ROOM_DIR + WEST, "west");
    add_exit(CAMP_ROOM_DIR + NE, "northeast", 0, 0, 1);
    add_exit(CAMP_ROOM_DIR + SW, "southwest", 0, 0, 1);
    add_exit(CAMP_ROOM_DIR + SE, "southeast", 0, 0, 1);


    add_forest();
    forest_herbs_1();
    if(!random(3))
    {
    forest_climb("f13_up");
    }
add_guard_down();
}

void
reset_room()
{
    set_searched(0);
}



