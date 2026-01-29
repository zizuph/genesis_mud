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

#define NORTH    "f19"
#define SOUTH    "f31"
#define EAST    "f28"
#define WEST    "f26"
#define SW        "f30"
#define NW        "m21"
#define NE        "f20"


object guard;

void
create_dunlending()
{
    set_short("In the foothills of the White Mountains");
    set_long("Giant pine trees dominate the landscape for as far as you can see. "
        + "Their trunks are so thick it would take several men to link hands "
        + "around them. Pine needles carpet the floor, interrupted here and "
        + "there by giant white-grey rocks. In the distance you can see "
        + "the White Mountains poking their peaks above the trees.\n");
        
    add_item( ({"mountain", "white mountain", "white mountains", "mountains"}),
        "The mountains look like jagged wolf teeth, jetting up toward the "
        + "sky. They are rugged, steep, and snow-capped--and rumor has it "
        + "trolls live in them.\n");
    add_item( ({"slope", "foothill", "foot hill", "foothills", "foot hills"}),
        "The foothills are quite rugged for just being foothills. They're "
        + "steep and difficult to climb, making you feel tired.\n");
    set_no_exit_msg( ({"northeast", "southeast"}), 
        "You have trouble getting any traction moving that direction.\n");
    add_item( ({"rock", "rocks", "granite", "granite rock", "granite rocks"}),
        "The rocks vary in size from very large to very very large, to quite "
        + "massive. They are a white-grey in color and make the foothills "
        + "look even more rugged than they are.\n");
    add_pinecone();
    
    add_exit(CAMP_ROOM_DIR + NORTH, "north");
    add_exit(CAMP_ROOM_DIR + SOUTH, "south");
    add_exit(CAMP_ROOM_DIR + EAST, "east");
    add_exit(CAMP_ROOM_DIR + WEST, "west");
    add_exit(CAMP_ROOM_DIR + NW, "northwest", 0, 0, 1);
    add_exit(CAMP_ROOM_DIR + SW, "southwest", 0, 0, 1);
    
    add_forest();
    forest_herbs_1();
    if(!random(3))
    {
    forest_climb("f27_up");
    }
add_guard_down();
}

void
reset_room()
{
        set_searched(0);}



