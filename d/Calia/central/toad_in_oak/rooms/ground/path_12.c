/* 
 * /d/Calia/central/toad_in_oak/rooms/ground/path_12.c
 *
 * A path on the southern edge of TiO
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
    set_short("A path beneath a village in the trees."); 
    set_long("You stand on a springy carpet of grass that stretches " + 
        "between the trunks of the gargantuan oaks of the forest. High " + 
        "overhead the branches of the trees support a small village. " + 
        "A short distance to the south there is a tangle of brush and " + 
        "branches that blocks any passage in that direction.\n"); 

    add_item(Grass_Words, grass_describe(({"northeast", "west"})));
    add_item(Thicket_Words, thicket_describe("south")); 
    add_item(Tree_Words, trees_describe(1, "north")); 
    add_item(Village_Words, village_describe()); 

    thicket_tells(); 

    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "path_13", "northeast"); 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "path_11", "west"); 
    add_exit( TOAD_IN_OAK_ROOMS_LOW + "walkway_11", "up"); 
}
