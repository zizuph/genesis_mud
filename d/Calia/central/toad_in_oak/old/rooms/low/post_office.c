/*
 * /d/Calia/central/toad_in_oak/rooms/low/post_office.c
 *
 * This is the general store in toad-in-Oak. 
 *
 * HISTORY: [99-06-22] Created by Kcirderf 
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

    set_short("The Toad-in-Oak Post Office"); 
    set_long("This is the post office of the village.\n"); 

    /*  Properties  */ 
    
    add_prop(ROOM_I_INSIDE, 1); 

    /*  Exits  */ 
     
    add_exit( TOAD_IN_OAK_ROOMS_LOW + "walkway_16", "east"); 
 
    /* items */ 

}
