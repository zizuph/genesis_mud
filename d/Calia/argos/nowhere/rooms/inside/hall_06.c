/*
 *  /d/Calia/argos/nowhere/rooms/outside/hall_06.c
 * 
 *  Part of the hallway inside the cliff complex, near
 *  the mine enterance. 
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
    add_exit( NOWHERE_ROOMS_INSIDE + "hall_05", "north"); 
    add_exit( NOWHERE_ROOMS_INSIDE + "mine_enterance", "southeast");  
}
