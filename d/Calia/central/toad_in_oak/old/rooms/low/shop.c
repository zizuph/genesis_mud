/*
 * /d/Calia/central/toad_in_oak/rooms/low/shop.c
 *
 * This is the general store in toad-in-Oak. 
 *
 * HISTORY: [99-06-19] Created by Kcirderf 
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

    set_short("The Toad-in-Oak General store"); 
    set_long("This is the villages general store, and the only shop in town " + 
        "that will buy anything from you. It's run by two brothers, Nahasa " + 
        "and Petilon, and their sister Peema.\n");     


    /*  Properties  */     

    add_prop(ROOM_I_INSIDE, 1); 

    /*  Exits  */ 
     
    add_exit( TOAD_IN_OAK_ROOMS_LOW + "walkway_14", "northeast"); 
 
    /* items */ 

}
