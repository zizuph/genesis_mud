/*
 *  /d/Calia/argos/nowhere/rooms/inside/baseroom_inside.c
 *
 *  This is the base room that will be inherited by all 
 *  "inside" rooms in Nowhere. That is rooms inside the 
 *  cliff, not necessarily rooms inside building outside 
 *  the cliff. This will contain any functions and 
 *  property settings specific to these rooms.
 *
 *  HISTORY: 2003-07-13 Created by Kcirderf
 *
 *  Copyright: Sean Dunphy (Kcirderf) 2003
 */ 

// INCLUSIONS AND DEFINITIONS

inherit "/d/Calia/argos/nowhere/rooms/baseroom.c"; 

#include <stdproperties.h>
#include "defs.h" 

// GLOBAL VARIABLES

// FORWARD FUNCTION DEFINITIONS

// FUNCTIONS

// ROOM DEFINITION

void 
create_nowhere_inside_room()
{
}

public nomask void
create_nowhere_room()
{
    set_short("A room in the cliff complex of Nowhere"); 
    set_long("A room in the cliff complex of Nowhere.\n"); 

    add_prop(ROOM_I_LIGHT, 1); 

    create_nowhere_inside_room();
}

