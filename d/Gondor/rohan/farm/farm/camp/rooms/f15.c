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

#define SOUTH    "f17"
#define WEST    "f14"
#define SW        "f16"
#define NW        "f11"
#define NE        "f12"


object guard;

void
create_dunlending()
{
    set_short("On the edge of a cliff in Anorien");
    set_long("A large cliff dominates the landscape here, dropping suddenly "
        + "into a ravine. Granite boulders hang over the ravine, and trees "
        + "grow on those boulders, their roots pushing down into cracks "
        + "and crevices. To the west and south, the forest continues "
        + "with old growth pine trees reaching to the sky.\n");
        
    add_item( ({"crack", "cracks", "crevice", "crevices"}),
        "The cracks are crevices are small gaps in the boulders where the "
        + "trees have fastened their roots.\n");
    set_no_exit_msg( ({"north", "east", "southeast", "northeast"}), 
        "Try as you might, you cannot find a trail leading that direction.\n");
    add_cliff();
    
    
    add_exit(CAMP_ROOM_DIR + SOUTH, "south");
    add_exit(CAMP_ROOM_DIR + WEST, "west");
    add_exit(CAMP_ROOM_DIR + NE, "northeast", 0, 0, 1);
    add_exit(CAMP_ROOM_DIR + NW, "northwest", 0, 0, 1);
    add_exit(CAMP_ROOM_DIR + SW, "southwest", 0, 0, 1);

    
    add_forest();
    forest_herbs_2();
    if(!random(3))
    {
    forest_climb("f15_up");
    }
add_guard_down();
}

void
reset_room()
{
        set_searched(0);}



