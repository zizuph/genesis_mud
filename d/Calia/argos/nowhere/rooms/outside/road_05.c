/*
 *  /d/Calia/argos/nowhere/rooms/outside/road_04.c
 * 
 *  Part of the road in Nowhere, at the entrance to the
 *  cliff complex
 *
 *  HISTORY: 2003-07-13 Created by Kcirderf
 *
 *  Copyright: Sean Dunphy (Kcirderf) 2003
 */ 

// INCLUSIONS AND DEFINITIONS

inherit "/d/Calia/argos/nowhere/rooms/outside/baseroom_outside.c";

#include <stdproperties.h>
#include "defs.h"

// ROOM DEFINITION

void 
create_nowhere_outside_room()
{
    add_exit( NOWHERE_ROOMS_INSIDE + "hall_01", "east"); 
    add_exit( NOWHERE_ROOMS_OUTSIDE + "road_06", "south"); 
    add_exit( NOWHERE_ROOMS_OUTSIDE + "road_04", "northwest"); 
}
