/*
 * /d/Calia/central/toad_in_oak/rooms/low/training.c
 *
 * This is the training area of TiO. The meditation spot will be 
 * elsewhere
 *
 * History: 2003-05-11 - Created by Kcirderf
 * 
 * Copyright: Sean Dunphy (Kcirderf) 2003
 */

// INCLUSIONS AND DEFINITIONS

inherit "/d/Calia/central/toad_in_oak/rooms/low/baseroom_low.c"; 

#include <stdproperties.h>
#include "defs.h"

// ROOM DEFINITION

void
create_tio_low_room()
{
    add_exit( TOAD_IN_OAK_ROOMS_LOW + "walkway_01",    "southeast"); 
}
