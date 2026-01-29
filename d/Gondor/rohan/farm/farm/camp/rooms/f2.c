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


object guard;

void
create_dunlending()
{
    set_short("Northwestern edge of a forest in Anorien");
    set_long("The forest floor is blanketed in pine needles and "
        + "pinecones. Thick underbrush prevents you from traveling "
        + "any further to the west, but to the south the forest "
        + "continues as far as you can see.\n");


    add_item( ({"underbrush", "brush"}), "The brush looks a lot like poison "
        + "oak! It's very thick and overgrown here, so you think it'd be "
        + "best not to walk through it.\n");
    add_pinecone();

    set_no_exit_msg( ({"north", "northwest", "west"}),
        "Thick underbrush prevents you from walking that direction.\n");

    add_exit(CAMP_ROOM_DIR + "f1", "northeast");
    add_exit(CAMP_ROOM_DIR + "f3", "east");
    add_exit(CAMP_ROOM_DIR + "f4", "southwest");
    add_exit(CAMP_ROOM_DIR + "f5", "south");
    add_exit(CAMP_ROOM_DIR + "f6", "southeast", 0,0,1);
    
    add_forest();
    forest_herbs_2();
    if(!random(3))
    {
    forest_climb("f2_up");
    }
add_guard_down();
}

void
reset_room()
{
        set_searched(0);}

