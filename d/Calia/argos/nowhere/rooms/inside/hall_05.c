/*
 *  /d/Calia/argos/nowhere/rooms/outside/hall_05.c
 * 
 *  Part of the hallway inside the cliff complex, with
 *  a secret exit to a room with controls for the 
 *  treasury alarm system. 
 *
 *  HISTORY: 2003-07-13 Created by Kcirderf
 *
 *  Copyright: Sean Dunphy (Kcirderf) 2003
 */ 

// INCLUSIONS AND DEFINITIONS

inherit "/d/Calia/argos/nowhere/rooms/inside/baseroom_inside.c";

#include <stdproperties.h>
#include "defs.h"

// ROOM DEFINITION

void 
create_nowhere_inside_room()
{
    add_exit( NOWHERE_ROOMS_INSIDE + "alarm", "east",0,1,1); 
    add_exit( NOWHERE_ROOMS_INSIDE + "hall_06", "south"); 
    add_exit( NOWHERE_ROOMS_INSIDE + "hall_04", "northwest"); 
}
