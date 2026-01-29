/*
 * /d/Calia/central/toad_in_oak/rooms/ground/entrance_north.c
 *
 * A path on the ground level of the village of Toad-In-Oak just 
 * inside the north entrance of the village. 
 * 
 * HISTORY: [99-07-22] Created by Kcirderf 
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

    set_short("The north entrance to Toad-in-Oak"); 

    set_long("This is the norht side entrance to the village. There will " +
        "be some sort of guard post occupied by " + 
        "npcs. Don't forget to put in the exit to the forest someday.\n"); 

    /*  Exits  */ 

    // add_exit("somewhere in the forest.", "north"); 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "path_13" , "south"); 

    /* items */ 

    

}        
