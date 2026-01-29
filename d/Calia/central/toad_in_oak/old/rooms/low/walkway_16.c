/*
 * /d/Calia/central/toad_in_oak/rooms/low/walkway_16.c
 *
 * This is one of walkways on the second level of the village. 
 *
 * HISTORY: [99-06-18] Created by Kcirderf 
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

    set_short("A walkway in Toad-in-Oak"); 
    set_long("This is part of the walkway on the second level of the " + 
        "village. Eventaully mortals should be able to see if there's any " + 
        "thing in the rooms on the ground below this one.\n");     

    /*  Exits  */ 
     
    add_exit( TOAD_IN_OAK_ROOMS_LOW + "walkway_17", "north"); 
    add_exit( TOAD_IN_OAK_ROOMS_LOW + "walkway_15", "southwest"); 
    add_exit( TOAD_IN_OAK_ROOMS_LOW + "post_office", "west"); 
 
    /* items */ 

}
