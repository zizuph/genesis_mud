/* 
 * /d/Calia/central/toad_in_oak/rooms/ground/green_ne.c
 *
 * The northeastern portion of the TiO village green. 
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
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "green_se", "south"); 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "gazebo", "southwest"); 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "green_nw", "west"); 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "path_10", "northwest"); 
}
