/*
 * /d/Calia/central/toad_in_oak/rooms/ground/garden_vegetable.c
 *
 * This is the Toad-in-Oak vegetable garden. 
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

// ROOM DEFINITION

void
create_tio_ground_room()
{
    /* Descriptions */ 

    set_short("The Toad-in-Oak vegetable garden"); 

    set_long("This is the elves veggie garden. They only grow a few " +
        "of their favorites and gather most of their food from the " + 
        "forest, so it's not terribly large. Players should be able " + 
        "to pick a few vegetables from here.\n"); 

    /*  Exits  */ 
    
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "path_08", "northwest"); 

    /* items */ 

}
