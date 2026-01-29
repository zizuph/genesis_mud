/*
 *  /d/Calia/argos/nowhere/rooms/outside/store.c
 * 
 *  The general store of Nowhere. 
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
    add_exit( NOWHERE_ROOMS_OUTSIDE + "road_04", "south"); 
}
