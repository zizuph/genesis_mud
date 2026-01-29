/*
 * /d/Calia/central/toad_in_oak/rooms/low/pub.c
 *
 * This is the lacal pub. 
 *
 * HISTORY: [99-06-19] Created by Kcirderf 
 *
 * Copyright (C): Kcirderf 1999
 *
 */

// INCLUSIONS AND DEFINITIONS

inherit "/d/Calia/central/toad_in_oak/rooms/low/base_low";

#include <stdproperties.h>
#include "defs.h"

// ROOM DEFINITION

void
create_tio_low_room()
{
    /* Descriptions */ 

    set_short("The Toad-in-Oak Pub"); 
    set_long("This is the local pub. It was established sometime after the " + 
        "war with kroug, and is mostly used by visitors to the village. It " + 
        "is possible to rent a small room here to stay the night.\n"); 
    
    /*  Properties  */ 

    add_prop(ROOM_I_INSIDE, 1); 

    /*  Exits  */ 
     
    add_exit( TOAD_IN_OAK_ROOMS_LOW + "walkway_11", "northeast"); 

    /* items */ 

}
