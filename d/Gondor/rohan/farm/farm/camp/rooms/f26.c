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

#define NORTH    "m21"
#define SOUTH    "f30"
#define EAST    "f27"
#define WEST    "f25"
#define SE        "f31"
#define NW        "m20"
#define NE        "f19"


object guard;

void
create_dunlending()
{
    set_short("In the foothills of the White Mountains");
    set_long("At the base of the foothills to the north, a wide meadow "
        + "opens up, with rich green grass and ample sunshine. To the "
        + "south, forested foothills continue rising toward the "
        + "White Mountains. Large granite rocks poke through the pine "
        + "needles here and there, in between the pine trees.\n");
        
    add_item( ({"mountain", "white mountain", "white mountains", "mountains"}),
        "The mountains look like jagged wolf teeth, jetting up toward the "
        + "sky. They are rugged, steep, and snow-capped--and rumor has it "
        + "trolls live in them.\n");
    add_item( ({"slope", "foothill", "foot hill", "foothills", "foot hills"}),
        "The foothills are quite rugged for just being foothills. They're "
        + "steep and difficult to climb, making you feel tired.\n");
    set_no_exit_msg( ({"southwest", "southeast"}), 
        "You have trouble getting any traction moving that direction.\n");
    add_item( ({"rock", "rocks", "granite", "granite rock", "granite rocks"}),
        "The rocks vary in size from very large to very very large, to quite "
        + "massive. They are a white-grey in color and make the foothills "
        + "look even more rugged than they are.\n");
    add_forest_meadow("north");
    
    add_exit(CAMP_ROOM_DIR + NORTH, "north");
    add_exit(CAMP_ROOM_DIR + SOUTH, "south");
    add_exit(CAMP_ROOM_DIR + EAST, "east");
    add_exit(CAMP_ROOM_DIR + WEST, "west");
    add_exit(CAMP_ROOM_DIR + NE, "northeast", 0, 0, 1);
    add_exit(CAMP_ROOM_DIR + NW, "northwest", 0, 0, 1);
    add_exit(CAMP_ROOM_DIR + SE, "southeast", 0, 0, 1);

    
    add_forest();
    forest_herbs_2();
    if(!random(3))
    {
    forest_climb("f26_up");
    }
add_guard_down();
}

void
reset_room()
{
        set_searched(0);}
