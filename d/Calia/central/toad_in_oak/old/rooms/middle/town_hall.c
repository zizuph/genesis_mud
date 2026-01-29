/*
 * /d/Calia/central/toad_in_oak/rooms/middle/town_hall.c
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

    set_short("The villages 'town hall'"); 
    set_long("This is the 'town hall' of the village. I have no idea what " +
        "I'm going to do with this room actually.\n"); 

    /*  Properties  */     

    add_prop(ROOM_I_INSIDE, 1); 

    /*  Exits  */ 
     
    add_exit( TOAD_IN_OAK_ROOMS_MIDDLE + "walkway_05", "west"); 

    /* items */ 

}
