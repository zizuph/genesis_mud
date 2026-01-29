/*
 * /d/Calia/central/toad_in_oak/rooms/low/tailor.c
 *
 * This is the tailor's shop in the village. 
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

    set_short("The Toad-in-Oak Tailor"); 
    set_long("This is the home of the tailor in Toad-in-Oak. Mortals will " + 
        "able to order a number of custom made clothing items.\n");        

    /*  Properties  */     

    add_prop(ROOM_I_INSIDE, 1); 

    /*  Exits  */ 
     
    add_exit( TOAD_IN_OAK_ROOMS_LOW + "walkway_07", "west"); 
 
    /* items */ 

}
