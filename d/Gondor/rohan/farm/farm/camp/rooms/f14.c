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

#define NORTH    "f11"
#define SOUTH    "f16"
#define EAST    "f15"
#define WEST    "f13"
#define SE        "f17"
#define SW        "m12"
#define NW        "m7"


object guard;

void
create_dunlending()
{
    set_short("In the middle of a forest in Anorien");
    set_long("Pine trees, straight and tall, nearly block the sun "
        + "with their wide branches. The forest floor is a carpet of "
        + "pine needles with just a few herbs popping up here and there, "
        + "especially on the edges of the forest near the meadow. The "
        + "occasional woodland creature wanders around here, making "
        + "tracks on the ground.\n");
        
    add_item( ({"track", "tracks", "ground"}), "You see wolf, deer, and "
        + "even rabbit tracks on the ground.\n");
    
    set_no_exit_msg( ({"northeast"}), 
        "Try as you might, you cannot find a trail leading northeast.\n");
    add_forest_meadow("northwest and southwest");
    add_pinecone();
    
    add_exit(CAMP_ROOM_DIR + NORTH, "north");
    add_exit(CAMP_ROOM_DIR + SOUTH, "south");
    add_exit(CAMP_ROOM_DIR + EAST, "east");
    add_exit(CAMP_ROOM_DIR + WEST, "west");
    add_exit(CAMP_ROOM_DIR + NW, "northwest", 0, 0, 1);
    add_exit(CAMP_ROOM_DIR + SW, "southwest", 0, 0, 1);
    add_exit(CAMP_ROOM_DIR + SE, "southeast", 0, 0, 1);

    
    add_forest();
    forest_herbs_1();
    if(!random(3))
    {
    forest_climb("f14_up");
    }
add_guard_down();
}

void
reset_room()
{
        set_searched(0);}



