/* 
 * /d/Calia/central/toad_in_oak/rooms/ground/swim_shore.c
 *
 * This is the edge of the swimming hole on the hill east of 
 * Toad-in-Oak. The layout of this area may change a bit when it
 * is actually filled in. 
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
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "trail_04", "northwest"); 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "swim", "enter"); 
}
