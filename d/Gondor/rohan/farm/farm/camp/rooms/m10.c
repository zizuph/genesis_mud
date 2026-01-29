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

#define TENT    "_a_tent_sits_here"

#define NORTH    "m8"
#define SOUTH    
#define EAST    "m11"
#define WEST    
#define SE        "m14"
#define SW        "m13"
#define NW        
#define NE        "m9"


object guard;

void
create_dunlending()
{
    set_short("In the midst of a meadow in Anorien");
    set_long("For as far as you can see, there is an open meadow. "
        + "Campfire smoke indicates that you are, in fact, not alone here. "
        + "Judging from the harsh conversations you hear carried on the "
        + "wind, humans are about, and in some numbers too. "
        + "@@extra_line@@" + "To the south you notice the White Mountains "
        + "and their jagged, snow-capped peaks.\n");

    add_item( ({"mountain", "mountains", "white mountain", "white mountains"}),
        "The White Mountains look tall and imposing from here. Rumor has it "
        + "that trolls live in the deep crevices and caves of those "
        + "mountains.\n");
        
    set_no_exit_msg( ({"west", "northwest", "south"}), "You "
        + "cannot find a trail leading in that direction.\n");
        
    add_exit(CAMP_ROOM_DIR + NORTH, "north");
//    add_exit(CAMP_ROOM_DIR + SOUTH, "south");
    add_exit(CAMP_ROOM_DIR + EAST, "east");
//    add_exit(CAMP_ROOM_DIR + WEST, "west");
    add_exit(CAMP_ROOM_DIR + NE, "northeast", 0, 0, 1);
//    add_exit(CAMP_ROOM_DIR + NW, "northwest");
    add_exit(CAMP_ROOM_DIR + SW, "southwest");
    add_exit(CAMP_ROOM_DIR + SE, "southeast", 0, 0, 1);

    add_room_tell("You hear something snarling in the grass.");
    add_room_tell("You hear men taking. They said something about horse meat "
        + "being delicious.");
    add_room_tell("You overhear a woman speaking: Edora... and cut... out.");
    add_room_tell("You hear people laughing viciously.");
    



    add_meadow();
    meadow_herbs_2();
    if(!random(3))
    {
        TO->add_prop(TENT, 1);
    enter_tent("m10t");
    }
    add_guard_down();
}

void
reset_room()
{
    set_searched(0);
}




