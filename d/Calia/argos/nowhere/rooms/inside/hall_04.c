/*
 *  /d/Calia/argos/nowhere/rooms/outside/hall_04.c
 * 
 *  Part of the hallway inside the cliff complex, outside
 *  of the treasurer's guard post
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
    add_exit( NOWHERE_ROOMS_INSIDE + "guard", "east"); 
    add_exit( NOWHERE_ROOMS_INSIDE + "hall_05", "southeast"); 
    add_exit( NOWHERE_ROOMS_INSIDE + "hall_02", "northwest"); 
}
