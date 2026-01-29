/* 
 *  /d/Calia/central/toad_in_oak/rooms/middle/baseroom_middle.c
 *
 * This is the base room that will be inherited by rooms on the
 * 'middle' level of the village (The second level of walkways above
 * the ground), and provides a few functions and property settings 
 * specific to this level. 
 * 
 * HISTORY: 2003-05-11 - Created by Kcirderf 
 *
 * Copyright: Sean Dunphy (Kcirderf) 2003
 */ 

// INCLUSIONS AND DEFINITIONS

inherit "/d/Calia/central/toad_in_oak/rooms/baseroom.c"; 

#include <stdproperties.h>
#include "defs.h"

// FUNCTIONS

// ROOM DEFINITION

void 
create_tio_middle_room()
{
}

public nomask void
create_tio_room()
{
    set_short ("A room on the middle level of Toad-in-Oak"); 
    set_long ("A room on the middle level of Toad-in-Oak.\n"); 

    add_prop(OBJ_I_LIGHT, 2); 
    
    create_tio_middle_room(); 
}

