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

#define NORTH    "f26"
#define EAST    "f31"
#define SE        "m24"
#define NW        "f25"
#define NE        "f27"


object guard;

void
create_dunlending()
{
    set_short("In a forest in Anorien");
    set_long("High up in the foothills of the White Mountains, "
        + "You look out and see the pine forest to your north. "
        + "The forest stretches nearly as far as you can see, "
        + "broken up only occasionaly by meadows such as the one to "
        + "the southeast.\n");
    
    add_item( ({"mountain", "white mountain", "white mountains", "mountains"}),
        "The mountains look like jagged wolf teeth, jetting up toward the "
        + "sky. They are rugged, steep, and snow-capped--and rumor has it "
        + "trolls live in them.\n");
    add_item( ({"slope", "foothill", "foot hill", "foothills", "foot hills"}),
        "The foothills are quite rugged for just being foothills. They're "
        + "steep and difficult to climb, making you feel tired.\n");
    
    set_no_exit_msg( ({"south", "west", "southwest"}), 
        "Thick undergrowth prevents you from moving in that direction.\n");
    add_item("undergrowth", "The undergrowth is thick here. You notice "
        + "poison oak as well as some bushes with thorns on them. You would "
        + "not be able to walk through the undergrowth.\n");
    add_forest_meadow("southeast");
    
    add_exit(CAMP_ROOM_DIR + NORTH, "north");
    add_exit(CAMP_ROOM_DIR + EAST, "east");
    add_exit(CAMP_ROOM_DIR + NE, "northeast", 0, 0, 1);
    add_exit(CAMP_ROOM_DIR + NW, "northwest");
    add_exit(CAMP_ROOM_DIR + SE, "southeast");

    
    add_forest();
    forest_herbs_2();
    if(!random(3))
    {
    forest_climb("f30_up");
    }
add_guard_down();
}

void
reset_room()
{
        set_searched(0);}


