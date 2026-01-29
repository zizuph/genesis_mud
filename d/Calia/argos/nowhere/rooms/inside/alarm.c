/*
 *  /d/Calia/argos/nowhere/rooms/outside/alarm.c
 * 
 *  Room with the treasury alarm controls
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
    add_exit( NOWHERE_ROOMS_INSIDE + "hall_05", "south",0,1,1); 
}
