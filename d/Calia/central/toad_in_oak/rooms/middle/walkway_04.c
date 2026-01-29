/*
 * /d/Calia/central/toad_in_oak/rooms/middle/walkway_04.c
 *
 * A portion of the walkway on the middle level of Toad-in-Oak
 *
 * History: 2003-05-11 - Created by Kcirderf
 * 
 * Copyright: Sean Dunphy (Kcirderf) 2003
 */

// INCLUSIONS AND DEFINITIONS

inherit "/d/Calia/central/toad_in_oak/rooms/middle/baseroom_middle.c"; 

#include <stdproperties.h>
#include "defs.h"

// ROOM DEFINITION

void
create_tio_middle_room()
{
    add_exit( TOAD_IN_OAK_ROOMS_MIDDLE + "home_02",       "northeast"); 
    add_exit( TOAD_IN_OAK_ROOMS_MIDDLE + "walkway_05",    "south"); 
    add_exit( TOAD_IN_OAK_ROOMS_MIDDLE + "walkway_03",    "northwest"); 
}

