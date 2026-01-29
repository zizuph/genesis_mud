/*
 * /d/Calia/central/toad_in_oak/rooms/ground/entrance_west.c
 *
 * A path on the ground level of the village of Toad-In-Oak just 
 * inside the west entrance of the village. 
 * 
 * HISTORY: [99-06-15] Created by Kcirderf 
 *
 * Copyright (C): Kcirderf 1999
 *
 */

// INCLUSIONS AND DEFINITIONS

inherit "/d/Calia/central/toad_in_oak/rooms/ground/base_ground";

#include <stdproperties.h>
#include "defs.h"
#include "stream_drink.h" /* Code to allow drinking from 
                                            the stream */ 

// ROOM DEFINITION

void
create_tio_ground_room()
{
    /* Descriptions */ 

    set_short("The west entrance to Toad-in-Oak"); 

    set_long("This is the west side entrance to the village. The stream " + 
        "runs by, and there will be some sort of guard post occupied by " + 
        "npcs. Don't forget to put in the exit to the forest someday.\n"); 

    /*  Properties  */     
 
    add_prop(ROOM_I_TYPE, ROOM_BEACH); /*   Not a true beach, but 
                                            next to a stream. */ 
    add_prop(OBJ_I_CONTAIN_WATER, -1); /*   Infinite water due to the                                            stream */ 

    /*  Exits  */ 

    // add_exit("somewhere in the forest.", "west"); 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "path_01" , "east"); 

    /* items */ 

    

}

void
init() 
{
    ::init();

    add_action(drink_stream, "drink"); 
}

 
        
