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
    set_short("In a forest, near a meadow in Anorien");
    set_long("To the south, you see a wide-open meadow. Here, the "
        + "trees are wide apart and you can see patches of grass "
        + "poking up between the pine needles. The pine needles "
        + "look disturbed, as if something--or someone--recently "
        + "walked through here.\n");


    add_item( ({"underbrush", "brush"}), "The brush looks a lot like poison "
        + "oak! It's very thick and overgrown here, so you think it'd be "
        + "best not to walk through it.\n");
    add_item( ({"needles", "pine needles", "pineneedles"}), 
        "Lifting up the pine needles, you notice some deer tracks in the "
        + "dirt.\n");
    add_item(({"tracks", "deer tracks", "dirt"}), "Yes, it seems deer have "
        + "been walking through here.\n");
    add_forest_meadow("south and southwest");
    set_no_exit_msg( ({"northwest", "west"}),
        "Thick underbrush prevents you from walking that direction.\n");

    add_exit(CAMP_ROOM_DIR + "f2", "northeast");
    add_exit(CAMP_ROOM_DIR + "f5", "east");
    add_exit(CAMP_ROOM_DIR + "m1", "southwest");
    add_exit(CAMP_ROOM_DIR + "m2", "south");
    add_exit(CAMP_ROOM_DIR + "f7", "southeast", 0,0,1);

    
    add_forest();
    forest_herbs_3();
    if(!random(3))
    {
    forest_climb("f4_up");
    }
add_guard_down();
}

void
reset_room()
{
        set_searched(0);}
