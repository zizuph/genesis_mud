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

#define WEST    "f28"
#define NW        "f20"


object guard;

void
create_dunlending()
{
    set_short("Deep in a forest in Anorien");
    set_long("Underbrush chokes off most trails and paths through this "
        + "portion of the forest, leaving few ways open. Large pine trees "
        + "nearly black out the sky, their branches almost entertwined "
        + "far above your head. Somewhere to the northwest is a meadow, "
        + "but it's hard to tell from here. One section of "
        + "the forest looking very much like the others.\n");
    
    set_no_exit_msg( ({"north", "south", "east", "southeast", "southwest", "northeast"}), 
        "Thick undergrowth prevents you from moving in that direction.\n");
    add_item("undergrowth", "The undergrowth is thick here. You notice "
        + "poison oak as well as some bushes with thorns on them. You would "
        + "not be able to walk through the undergrowth.\n");
    add_pinecone();
    

    add_exit(CAMP_ROOM_DIR + WEST, "west");
    add_exit(CAMP_ROOM_DIR + NW, "northwest");

    
    add_forest();
    forest_herbs_2();
    if(!random(3))
    {
    forest_climb("f29_up");
    }
add_guard_down();
}

void
reset_room()
{
        set_searched(0);}



