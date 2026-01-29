/* 
 * /d/Calia/central/toad_in_oak/rooms/ground/green_se.c
 *
 * The southeastern portion of the TiO village green. 
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
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "green_ne", "north"); 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "path_11", "southeast"); 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "green_sw", "west"); 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "gazebo", "northwest"); 

}
