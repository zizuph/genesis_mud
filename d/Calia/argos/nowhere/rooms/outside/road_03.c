/*
 *  /d/Calia/argos/nowhere/rooms/outside/road_03.c
 * 
 *  Part of the road in Nowhere, outside of the AG
 *
 *  HISTORY: 2003-07-13 Created by Kcirderf
 *
 *  Copyright: Sean Dunphy (Kcirderf) 2003
 */ 

// INCLUSIONS AND DEFINITIONS

#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include "defs.h"

inherit "/d/Calia/argos/nowhere/rooms/outside/baseroom_outside.c";

// ROOM DEFINITION

void 
create_nowhere_outside_room()
{

    set_short("A road through a small village.");   
    set_long("You stand on a stone road that winds its way between " + 
        "a number of low stone houses. A large cliff towers over the " + 
        "eastern side of this small village. A larger building with " + 
        "a slate roof stands to the north of the road.\n"); 

    add_item(({"building", "stone building", "large building", 
       "larger building"}), 
        "There is a stone building larger than the surrounding houses " + 
        "just to the north of the road here. It is constructed in the " + 
        "same way of the same stone as the houses, but is wider, and the " + 
        "wall are at least three feet taller than any of the houses. The " + 
        "roof is made from slate tiles rather than thatch. There is a " + 
        "window and a wooden door on the front of the building, but no " + 
        "indication as to what is inside.\n"); 

    add_item(({"door", "wooden door"}), 
        "A solid, well maintained, wooden door leads into the building " + 
        "to the north.\n"); 
    
    add_item(({"window"}), 
        "The glass of the window is too grimy to see what is inside the " + 
        "building.\n"); 

    add_item(({"roof", "slate roof", "tiles", "slate tiles"}), 
        "The roof of the building north of the road is made up of " + 
        "overlapping tiles of gray slate.\n"); 

    add_item(Cliff_Words, describe_cliff()); 
    add_item(House_Words, describe_houses()); 
    add_item(Road_Words, describe_road(({"south", 
        "east, turning southeast to avoid a building"}))); 
    add_item(Village_Words, describe_village());     
        
    add_exit( NOWHERE_ROOMS_OUTSIDE + "adv_guild", "north"); 
    add_exit( NOWHERE_ROOMS_OUTSIDE + "road_04", "east"); 
    add_exit( NOWHERE_ROOMS_OUTSIDE + "road_02",  "south"); 
}



