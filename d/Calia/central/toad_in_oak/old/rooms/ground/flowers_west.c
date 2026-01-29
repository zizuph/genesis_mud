/*
 * /d/Calia/central/toad_in_oak/rooms/ground/garden_flower_west.c
 *
 * This is the western corner of the Toad-in-Oak flower garden
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

    set_short("The Toad-in-Oak flower garden"); 

    set_long("This is the Toad-in-Oak flower garden. It will be full of " + 
        "colourful flowers. There will be common flowers of many types for " + 
        "mortals to pick, and a few rare unique types. Somewhere in the " + 
        "area there should be a few benches and so on. Butterflies will " + 
        "move around here, and there may be a florist of sorts.\n"); 

    /*  Exits  */ 
    
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "flowers_north" , "north" ); 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "flowers_east" , "east"); 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "flowers_south" , "southeast"); 
    add_exit( TOAD_IN_OAK_ROOMS_GROUND + "path_10" , "northwest"); 

    /* items */ 

}
