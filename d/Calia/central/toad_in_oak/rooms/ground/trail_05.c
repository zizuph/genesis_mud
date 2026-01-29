/* 
 * /d/Calia/central/toad_in_oak/rooms/ground/trail_05.c
 *
 * Part of the trail up the hill east of TiO
 * 
 * HISTORY: 2003-05-11 Created by Kcirderf
 *
 * Copyright: Sean Dunphy (Kcirderf) 2003
 */ 

// INCLUSIONS AND DEFINITIONS

inherit "/d/Calia/central/toad_in_oak/rooms/ground/baseroom_ground.c";

#include <stdproperties.h>
#include "defs.h"

// ROOM DEFINITION

void
create_tio_ground_room()
{
    set_short("On the side of a hill in the forest."); 
    set_long("You stand on the side of a hill overlooking a large pool " + 
        "of water. All around you are colossal oaks reaching high " +
        "into the sky. The ground betweek the trees is covered in a " + 
        "carpet of grass. Downhill to the northeast you can see a dense " + 
        "thicket of vegetation that forms a wall between the hill and " +
        "the greater forest.\n");         

    add_item(Grass_Words, trail_describe("southwest", "northwest")); 
    add_item(Hill_Words, hill_describe()); 
    add_item(Swim_Words, "@@swim_describe@@"); 
    add_item(Tree_Words, trees_describe(0, "")); 
    add_item(Thicket_Words, thicket_describe("northeast.")); 

    add_tell("You hear the sound of falling water somewhere nearby."); 
    
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "trail_06", "southeast"); 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "trail_04", "west"); 
}
