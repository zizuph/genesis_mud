/* 
 * /d/Calia/central/toad_in_oak/rooms/ground/flowers_w.c
 *
 * The western portion of the TiO flower gardens. 
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
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "flowers_n", "north"); 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "flowers_e", "east"); 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "flowers_s", "southeast");
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "path_05", "northwest");
}
