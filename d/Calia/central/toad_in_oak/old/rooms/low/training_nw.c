/*
 * /d/Calia/central/toad_in_oak/rooms/low/training_nw.c
 *
 * This is the northwest corner of the villages training area. 
 *
 * HISTORY: [99-06-22] Created by Kcirderf 
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

    set_short("The Toad-in-Oak Training Platform"); 
    set_long("This is part of the large platform that the elves of " + 
        "the village use for training and practicing their combat skills. " + 
        "Somewhere on this platform will be an NPC who acts as an " + 
        "adventurer's guild,\n"); 

    /*  Exits  */ 
     
    add_exit( TOAD_IN_OAK_ROOMS_LOW + "training_ne", "east"); 
    add_exit( TOAD_IN_OAK_ROOMS_LOW + "training_se", "southeast"); 
    add_exit( TOAD_IN_OAK_ROOMS_LOW + "training_sw", "south"); 

    /* items */ 

}
