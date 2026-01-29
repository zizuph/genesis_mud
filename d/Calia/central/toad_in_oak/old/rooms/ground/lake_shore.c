/*
 * /d/Calia/central/toad_in_oak/rooms/ground/lake_shore.c
 *
 * This is the edge of the "lake" east of the village
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
        "before continuing down the hill. This area will be guarded by " + 
        "some sort of large frogs that will insure that people are properly " + 
        "dressed (ie. wearing nothing) before swimming, and that people " + 
        "don't steal others things, or try to wander off naked. The 'in' " + 
        "exit is temporary and will be replaced by more appropriate " + 
        "commands when this area is finished.\n"); 

    /*  Properties  */     

    add_prop(ROOM_I_TYPE, ROOM_BEACH);
    add_prop(OBJ_I_CONTAIN_WATER, -1); 

    /*  Exits  */ 
    
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "trail_04", "northwest"); 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "lake_swimming" , "in"); 

    /* items */ 

}
