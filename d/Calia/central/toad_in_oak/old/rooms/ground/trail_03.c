/*
 * /d/Calia/central/toad_in_oak/rooms/ground/trail_03.c
 *
 * Part of the trail to teh swimming hole and the spring. It's called 
 * a "trail" just to keep it separate from the "path" rooms. 
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

    set_short("A trail east of Toad-in-Oak"); 

    set_long("This is the trail that leads to the swimming area and the " + 
        "spring where the stream starts east of the village. The path here " + 
        "will be a little more obvious than in the center of the village " + 
        "because this area is not as well tended by the elves.\n"); 

    /*  Exits  */ 
    
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "trail_04", "east"); 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "trail_02", "west"); 
    
    /* items */ 

}
