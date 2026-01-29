/* 
 * /d/Calia/central/toad_in_oak/rooms/ground/trail_02.c
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
    set_long("You stand among the trunks of the tremendous oak trees on " + 
        "the side of a hill. Green grass fills the patches of ground " + 
        "between their trunks. High in the branches of the trees to the " + 
        "west you can see the underside of a village.\n"); 

    add_item(Grass_Words, trail_describe("east", "northwest")); 
    add_item(Hill_Words, hill_describe()); 
    add_item(Tree_Words, trees_describe(0, "")); 
    add_item(Village_Words, village_describe()); 
    
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "trail_03", "east"); 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "trail_01", "northwest"); 
}
