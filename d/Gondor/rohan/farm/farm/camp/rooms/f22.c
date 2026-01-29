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

#define NORTH    "m17"
#define SOUTH    "m22"
#define EAST    "f23"
#define WEST    "f21"
#define NE      "m18"

object guard;

void
create_dunlending()
{
    set_short("In a forest near a meadow in Anorien");
    set_long("To the north and south are open meadows. East and west "
        + "of you large pine trees dominate the landscape, their branches "
        + "far above your head, their pineneedles underneath your feet. "
        + "From time to time, you see the White Mountains' peaks poking "
        + "through the trees.\n");
        
    
    set_no_exit_msg( ({ "northwest", "southwest", "southeast"}), 
        "You have trouble getting any traction moving that direction.\n");

    add_forest_meadow("north and south");
    
    add_exit(CAMP_ROOM_DIR + NORTH, "north");
    add_exit(CAMP_ROOM_DIR + SOUTH, "south");
    add_exit(CAMP_ROOM_DIR + EAST, "east");
    add_exit(CAMP_ROOM_DIR + WEST, "west");
    add_exit(CAMP_ROOM_DIR + NE, "northeast", 0, 0, 1);

    
    add_forest();
    forest_herbs_2();
    if(!random(3))
    {
    forest_climb("f22_up");
    }
add_guard_down();
}

void
reset_room()
{
        set_searched(0);}



