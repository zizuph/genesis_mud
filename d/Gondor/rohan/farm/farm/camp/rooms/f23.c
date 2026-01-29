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

#define NORTH    "m18"
#define SOUTH    
#define EAST    "f24"
#define WEST    "f22"
#define SE        "m23"
#define SW        
#define NW        "m17"
#define NE        "m19"


object guard;

void
create_dunlending()
{
    set_short("A forest in the foothills of the White Mountains");
    set_long("A large meadow stretches far to the north, and "
        + "a small meadow lies just to the south. The flat forest land "
        + "has given way to the rugged foothills "
        + "here. The mountains look closer, and the slopes steeper, "
        + "as you make your way up the foothills.\n");
        
    add_item( ({"mountain", "white mountain", "white mountains", "mountains"}),
        "The mountains look like jagged wolf teeth, jetting up toward the "
        + "sky. They are rugged, steep, and snow-capped--and rumor has it "
        + "trolls live in them.\n");
    add_item( ({"slope", "foothill", "foot hill", "foothills", "foot hills"}),
        "The foothills are quite rugged for just being foothills. They're "
        + "steep and difficult to climb, making you feel tired.\n");
    set_no_exit_msg( ({ "northwest", "southwest", "southeast"}), 
        "You have trouble getting any traction moving that direction.\n");

    add_forest_meadow("north and southeast");
    
    add_exit(CAMP_ROOM_DIR + NORTH, "north");
    add_exit(CAMP_ROOM_DIR + EAST, "east");
    add_exit(CAMP_ROOM_DIR + WEST, "west");
    add_exit(CAMP_ROOM_DIR + NE, "northeast", 0, 0, 1);
    add_exit(CAMP_ROOM_DIR + NW, "northwest", 0, 0, 1);
    add_exit(CAMP_ROOM_DIR + SE, "southeast");

    
    add_forest();
    forest_herbs_2();
    if(!random(3))
    {
        forest_climb("f23_up");
    }

    add_guard_down();
}

void
reset_room()
{
        set_searched(0);}



