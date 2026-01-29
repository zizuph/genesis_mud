/* 
 * /d/Calia/central/toad_in_oak/rooms/ground/flowers_n.c
 *
 * The northern portion of the TiO flower gardens. 
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
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "flowers_e", "southeast"); 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "flowers_w", "south"); 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "path_05", "west");
}
