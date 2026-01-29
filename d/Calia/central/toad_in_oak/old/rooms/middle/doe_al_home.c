/*
 * /d/Calia/central/toad_in_oak/rooms/middle/doe_al_home.c
 *
 * This is the home of the heroes mentioned in the Chronicles, 
 * Doe and Allerdice
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

    set_short("Doe & Allerdice's Home"); 
    set_long("This is the home of the heroes of the war with Kroug. Doe " +
        "and Allerdice ahve both become very important in the community " + 
        "and may even have a child.\n"); 

    /*  Properties  */     

    add_prop(ROOM_I_INSIDE, 1); 

    /*  Exits  */ 
     
    add_exit( TOAD_IN_OAK_ROOMS_MIDDLE + "walkway_01", "southeast"); 

    /* items */ 

}
