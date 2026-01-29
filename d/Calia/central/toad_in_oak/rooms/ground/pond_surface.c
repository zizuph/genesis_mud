/* 
 * /d/Calia/central/toad_in_oak/rooms/ground/pond_surface.c
 *
 * This is the surface of the pond beneath Toad-in-Oak. It will
 * not be reachable by mortals, but the contents can be seen from 
 * the edges. It exists so ducks and other critters can occasionally
 * be out of reach of players. 
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
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "pond_shore", "exit"); 
}
