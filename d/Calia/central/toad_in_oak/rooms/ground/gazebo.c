/* 
 * /d/Calia/central/toad_in_oak/rooms/ground/gazebo.c
 *
 * This is the gazebo in the center of the village green. It is
 * actually a living oak tree which has grown into a very strange 
 * shape. (For a tree, pretty standard for a gazebo.)
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
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "green_nw", "northwest"); 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "green_ne", "northeast"); 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "green_sw", "southwest"); 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "green_se", "southeast"); 

}
