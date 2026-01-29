/* 
 * /d/Calia/central/toad_in_oak/rooms/ground/pond_shore.c
 *
 * This is the edge of the pond beneath TiO. There will not 
 * be an entrance to the pond room when this is finished. 
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
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "path_04", "northwest"); 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "pond_surface", "enter"); 
}
