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

#define NORTH    
#define SOUTH    "f14"
#define EAST    "f12"
#define WEST     "m7"
#define SE        "f15"
#define SW        "f13"
#define NW        "m4"
#define NE        "m5"


object guard;

void
create_dunlending()
{
    set_short("In a forest, near a meadow");
    set_long("The pine needles on the ground are disturbed, "
        + "making what seems to be a trail. Lots of foot traffic "
        + "has come this way recently, mostly heading toward "
        + "the meadow to the "
        + "west. Looking east, you see the forest stops abruptly, "
        + "but you can't quite see why from here.\n");
    add_item( ({"path", "ground", "trail", "needles", "pine needles"}),
        "You see the pine needles have been pushed off to the sides, "
        + "exposing a line of bare dirt that looks to have been used "
        + "as a trail. You see some tracks on the ground.\n");
    add_item( ({"track", "tracks", "bootprint", "boot print", "bootprints", "boot prints"}),
        "Heavy boot prints mark the ground here. Soldiers have been walking from "
        +"the meadow into the forest.\n");

    add_forest_meadow("west and north");
    
    add_exit(CAMP_ROOM_DIR + SOUTH, "south");
    add_exit(CAMP_ROOM_DIR + EAST, "east");
    add_exit(CAMP_ROOM_DIR + WEST, "west");
    add_exit(CAMP_ROOM_DIR + NE, "northeast");
    add_exit(CAMP_ROOM_DIR + NW, "northwest", 0, 0, 1);
    add_exit(CAMP_ROOM_DIR + SW, "southwest", 0, 0, 1);
     add_exit(CAMP_ROOM_DIR + SE, "southeast", 0, 0, 1);

    
    add_forest();
    forest_herbs_3();
    if(!random(3))
    {
    forest_climb("f11_up");
    }
add_guard_down();
}

void
reset_room()
{
    set_searched(0);
}



