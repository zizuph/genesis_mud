/*
 * /d/Calia/central/toad_in_oak/rooms/low/restaurant.c
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

    set_short("The Toad-in-0ak eating area"); 
    set_long("This is a fairly large area where most of the elves in the " + 
        "eat most of their meals. They will allow outsiders to eat here for " + 
        "a price. The food should be helthy, but odd, vegetarian dishes.\n"); 

    /*  Properties  */     

    add_prop(ROOM_I_INSIDE, 1); 

    /*  Exits  */ 
     
    add_exit( TOAD_IN_OAK_ROOMS_LOW + "walkway_03", "southwest"); 
 
    /* items */ 

}
