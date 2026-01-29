/* 
 * /d/Calia/central/toad_in_oak/rooms/ground/path_08.c
 *
 * A path on the northern edge of TiO, at the enterance to the village
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
    set_long("All around you huge oak trees reach high towards the sky. In " + 
        "their branches far above you can see the underside of a small " +
        "village. The ground between their trunks is covered in lush green " + 
        "grass up to a dense thicket that extends to the east and west.\n"); 

    add_item(Grass_Words, grass_describe(({"north", "south"}))); 
    add_item(Thicket_Words, thicket_describe("east and west")); 
    add_item(Tree_Words, trees_describe(0, "")); 
    add_item(Village_Words, village_describe());   

    thicket_tells();  

    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "path_07", "south"); 
}
