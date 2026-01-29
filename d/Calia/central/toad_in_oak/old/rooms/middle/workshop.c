/*
 * /d/Calia/central/toad_in_oak/rooms/middle/workshop.c
 *
 * This is the wood-shapers workshop for making small items. 
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

    set_short("The Wood-shapers Workshop"); 
    set_long("This is the 'workshop' of the villages magical " + 
        "wood-shapers. Here they create small obejects out of 'cut' " + 
        "branches and terach their art to youngsters with talent.\n"); 

    /*  Properties  */     

    add_prop(ROOM_I_INSIDE, 1); 

    /*  Exits  */ 
     
    add_exit( TOAD_IN_OAK_ROOMS_MIDDLE + "walkway_07", "northwest"); 

    /* items */ 

}
