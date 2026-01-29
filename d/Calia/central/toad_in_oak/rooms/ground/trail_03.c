/* 
 * /d/Calia/central/toad_in_oak/rooms/ground/trail_03.c
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
    set_long("You stand on the side of a hill in the forest of " + 
        "enormous oak trees. All around you lush grass covers the ground " + 
        "between the trunks of the trees like a springy green carpet.\n"); 
    
    add_item(Grass_Words, trail_describe("east", "west")); 
    add_item(Hill_Words, hill_describe()); 
    add_item(Tree_Words, trees_describe(0, "")); 

    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "trail_04", "east"); 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "trail_02", "west"); 
}
