/* 
 * /d/Calia/central/toad_in_oak/rooms/ground/trail_06.c
 *
 * Part of the trail up the hill east of TiO, next to the spring
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
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "spring", "southwest"); 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "trail_05", "northwest"); 
}
