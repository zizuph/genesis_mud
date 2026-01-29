/*
 * /d/Calia/central/toad_in_oak/rooms/ground/lake_swimming.c
 *
 * This is the actual pond for swimming in. 
 *
 * HISTORY: [99-06-17] Created by Kcirderf 
 *
 * Copyright (C): Kcirderf 1999
 *
 */

// INCLUSIONS AND DEFINITIONS

inherit "/d/Calia/central/toad_in_oak/rooms/ground/base_ground";

#include <stdproperties.h>
#include "defs.h"

// ROOM DEFINITION

void
create_tio_ground_room()
{
    /* Descriptions */ 

    set_short("A lake east of Toad-in-Oak"); 

    set_long("This is the 'swimming-hole' east of the village. Water comes " + 
        "down a short waterfall from the spring and forms this small pond " + 
        "before continuing down the hill. This room should be full of fun " + 
        "things to do while swimming, like splashing and showering in the " + 
        "waterfall.\n"); 

    /*  Properties  */     

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
    add_prop(OBJ_I_CONTAIN_WATER, -1); 

    /*  Exits  */ 
    
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "lake_shore", "out");     

    /* items */ 

}
