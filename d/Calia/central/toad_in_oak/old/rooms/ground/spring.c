/*
 * /d/Calia/central/toad_in_oak/rooms/ground/spring.c
 *
 * This is the spring that begins the Toad-in-Oak stream.
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

    set_short("A spring east of Toad-in-Oak"); 

    set_long("This is the area around the spring that begins the stream " + 
        "through the village. This rooms should have the spring, the top " + 
        "of the first waterfall, and the beggings of the plumbing to take " + 
        "water to the second level of the village. It should also have a " + 
        "pretty good view of the village since it is on a hill. Players " + 
        "should be able to drink from the stream of course.\n"); 

    /*  Properties  */     

    add_prop(ROOM_I_TYPE, ROOM_BEACH);
    add_prop(OBJ_I_CONTAIN_WATER, -1); 

    /*  Exits  */ 
    
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "trail_06", "northeast"); 
    
    /* items */ 

}
