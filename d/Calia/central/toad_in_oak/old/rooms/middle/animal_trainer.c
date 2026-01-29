/*
 * /d/Calia/central/toad_in_oak/rooms/middle/animal_trainer.c
 *
 * This is the home of an animal trainer
 *
 * HISTORY: [99-06-22] Created by Kcirderf 
 *
 * Copyright (C): Kcirderf 1999
 *
 */

// INCLUSIONS AND DEFINITIONS

inherit "/d/Calia/central/toad_in_oak/rooms/middle/base_middle"; 

#include <stdproperties.h>
#include "defs.h"

// ROOM DEFINITION

void
create_tio_middle_room()
{
    /* Descriptions */ 

    set_short("The Animal Trainers Home"); 
    set_long("This is the home of the villages most talented animal " + 
        "trainer. Mortals will be able to purchase pets that can do a few " +
        "little tricks. (No combat advantage.)\n"); 

    /*  Properties  */     

    add_prop(ROOM_I_INSIDE, 1); 

    /*  Exits  */ 
     
    add_exit( TOAD_IN_OAK_ROOMS_MIDDLE + "walkway_11", "east"); 

    /* items */ 

}
