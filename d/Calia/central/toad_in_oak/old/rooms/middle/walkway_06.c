/*
 * /d/Calia/central/toad_in_oak/rooms/middle/walkway_06.c
 *
 * This is one of the walkways on the third level of the village
 *
 * HISTORY: [99-06-22] Created by Kcirderf 
 *
 * Copyright (C): Kcirderf 1999
 *
 */

// INCLUSIONS AND DEFINITIONS

inherit "/d/Calia/central/toad_in_oak/rooms/middle/base_middle";

#include <stdproperties.h>
#include "defs.h"

// ROOM DEFINITION

void
create_tio_middle_room()
{
    /* Descriptions */ 

    set_short("A walkway in Toad-in-Oak"); 
    set_long("This is part of the walkway on the third level of the " + 
        "village.\n"); 

    /*  Exits  */ 
     
    add_exit( TOAD_IN_OAK_ROOMS_MIDDLE + "walkway_05", "north"); 
    add_exit( TOAD_IN_OAK_ROOMS_MIDDLE + "walkway_07", "southwest"); 

    /* items */ 

}
