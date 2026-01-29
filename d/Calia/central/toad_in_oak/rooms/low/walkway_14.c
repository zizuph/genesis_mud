/*
 * /d/Calia/central/toad_in_oak/rooms/low/walkway_14.c
 *
 * A portion of the walkway on the lower level of Toad-in-Oak
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
    add_exit( TOAD_IN_OAK_ROOMS_LOW + "walkway_13",    "south"); 
    add_exit( TOAD_IN_OAK_ROOMS_LOW + "walkway_15",    "west"); 
}
