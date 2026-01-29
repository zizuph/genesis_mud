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
    set_short("Northeastern edge of a forest in Anorien");
    set_long("You stand in a pine forest not far from the White "
        + "Mountains. Pine needles are scattered about underfoot "
        + "but you see some small herbs growing up through them. "
        + "Deep undergrowth blocks your way to the east, but "
        + "the forest continues to the south.\n");


    add_item( ({"underbrush", "brush"}), "The brush looks a lot like poison "
        + "oak! It's very thick and overgrown here, so you think it'd be "
        + "best not to walk through it.\n");


    set_no_exit_msg( ({"northeast", "northwest", "east", "southeast"}),
        "Thick underbrush prevents you from walking that direction.\n");

    add_exit(CAMP_ROOM_DIR + "f1", "north");
    add_exit(CAMP_ROOM_DIR + "f2", "west");
    add_exit(CAMP_ROOM_DIR + "f6", "south");
    add_exit(CAMP_ROOM_DIR + "f5", "southwest", 0,0,1);


    add_forest();
    forest_herbs_2();
    if(!random(3))
    {
    forest_climb("f3_up");
    }
add_guard_down();
}

void
reset_room()
{
    set_searched(0);
}

