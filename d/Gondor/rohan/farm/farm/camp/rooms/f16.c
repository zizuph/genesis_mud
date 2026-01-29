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

#define NORTH    "f14"
#define EAST    "f17"
#define WEST    "m12"
#define SE        "f18"
#define SW        "m16"
#define NW        "f13"
#define NE        "f15"


object guard;

void
create_dunlending()
{
    set_short("In a forest in Anorien");
    set_long("The peaks of the White Mountains appear almost like ghosts "
        + "through the trees, appearing and disappearing as you move. "
        + "A meadow opens to the west, and you can see its grass flattened and "
        + "trampled. There are tracks all over the ground.\n");
        
    add_item( ({"track", "tracks", "ground"}), "You see wolf, deer, and "
        + "even rabbit tracks on the ground.\n");
    add_item( ({"grass", "meadow"}), "Looking westward toward the meadow, "
        + "you see the grass has been trampled and flattened. It looks as if "
        + "someone recently had a tent set up in the meadow!\n");
    set_no_exit_msg( ({"south"}), 
        "Try as you might, you cannot find a trail leading south.\n");
    add_forest_meadow("southwest");
    
    
    add_exit(CAMP_ROOM_DIR + NORTH, "north");
    add_exit(CAMP_ROOM_DIR + EAST, "east");
    add_exit(CAMP_ROOM_DIR + WEST, "west");
    add_exit(CAMP_ROOM_DIR + NE, "northeast", 0, 0, 1);
    add_exit(CAMP_ROOM_DIR + NW, "northwest", 0, 0, 1);
    add_exit(CAMP_ROOM_DIR + SW, "southwest");
    add_exit(CAMP_ROOM_DIR + SE, "southeast", 0, 0, 1);

    
    add_forest();
    forest_herbs_1();
    if(!random(3))
    {
    forest_climb("f16_up");
    }
add_guard_down();
}

void
reset_room()
{
        set_searched(0);}



