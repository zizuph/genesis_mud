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

#define NORTH    "m19"
#define SOUTH    "m23"
#define EAST    "f25"
#define WEST    "f23"
#define NW        "m18"
#define NE        "m20"


object guard;

void
create_dunlending()
{
    set_short("A forest in the foothills of the White Mountains");
    set_long("Standing near the top of foothills of the White Mountains, "
        + "the forest stretches in every direction. "
        + "Below you, to the north, the trees look almost eye-level, but here, "
        + "up close, they look truly massive. "
        + "Even a troll couldn't reach the lowest branches.\n");
        
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
    add_exit(CAMP_ROOM_DIR + SOUTH, "south");
    add_exit(CAMP_ROOM_DIR + EAST, "east");
    add_exit(CAMP_ROOM_DIR + WEST, "west");
    add_exit(CAMP_ROOM_DIR + NE, "northeast", 0, 0, 1);
    add_exit(CAMP_ROOM_DIR + NW, "northwest", 0, 0, 1);
    
    add_forest();
    forest_herbs_1();
    if(!random(3))
    {
    forest_climb("f24_up");
    }
add_guard_down();
}

void
reset_room()
{
        set_searched(0);}
