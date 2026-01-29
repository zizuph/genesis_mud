/*
    /d/Calia/argos/nowhere/rooms/baseroom.c
   
    This is the base room that will be inherited by every room in 
    Nowhere and will provide any functions that every room needs
   
    HISTORY: 2003-07-13 Created by Kcirderf
   
    Copyright: Sean Dunphy (Kcirderf) 2003
*/ 

// INCLUSIONS AND DEFINITIONS

#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include "defs.h"

inherit "/d/Calia/std/room_tell_room.c";

// GLOBAL VARIABLES

// FUNCTIONS

/*  
    Name:       nowhere()
    Purpose:    Identifies this object as belonging to Nowhere
    Arguments:  None
    Returns:    1
*/
int 
nowhere()
{
    return 1;
}

// ROOM DEFINITION

void
create_nowhere_room()
{
}

public nomask void
create_room()
{
    set_short("A room in Nowhere"); 
    set_long("A room in Nowhere.\n"); 

    add_prop(ROOM_I_TYPE, ROOM_NORMAL); 

    create_nowhere_room(); 
}

