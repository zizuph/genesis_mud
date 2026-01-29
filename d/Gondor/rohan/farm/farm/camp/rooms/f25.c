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

#define NORTH    "m20"
#define EAST    "f26"
#define WEST    "f24"
#define SE        "f30"
#define NW        "m19"
#define NE        "m21"


object guard;

void
create_dunlending()
{
    set_short("In the foothills of the White Mountains");
    set_long("The foothills are quite rugged here, and tiring to walk "
        + "through. To the north and southeast are peaceful meadows. "
        + "Here you're in the middle of an old forest, with tall "
        + "pine trees growing in every direction. "
        + "Tiny herbs poke up from the carpet of pine needles "
        + "covering the forest floor.\n");
        
    add_item( ({"mountain", "white mountain", "white mountains", "mountains"}),
        "The mountains look like jagged wolf teeth, jetting up toward the "
        + "sky. They are rugged, steep, and snow-capped--and rumor has it "
        + "trolls live in them.\n");
    add_item( ({"slope", "foothill", "foot hill", "foothills", "foot hills"}),
        "The foothills are quite rugged for just being foothills. They're "
        + "steep and difficult to climb, making you feel tired.\n");
    set_no_exit_msg( ({"southwest", "southeast"}), 
        "You have trouble getting any traction moving that direction.\n");

    add_forest_meadow("north and south");
    
    add_exit(CAMP_ROOM_DIR + NORTH, "north");
    add_exit(CAMP_ROOM_DIR + EAST, "east");
    add_exit(CAMP_ROOM_DIR + WEST, "west");
    add_exit(CAMP_ROOM_DIR + NE, "northeast", 0, 0, 1);
    add_exit(CAMP_ROOM_DIR + NW, "northwest", 0, 0, 1);
    add_exit(CAMP_ROOM_DIR + SE, "southeast");

    
    add_forest();
    forest_herbs_1();
    if(!random(3))
    {
    forest_climb("f25_up");
    }
add_guard_down();
}

void
reset_room()
{
        set_searched(0);}
