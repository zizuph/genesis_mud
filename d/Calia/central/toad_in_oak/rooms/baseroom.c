/* 
    /d/Calia/central/toad_in_oak/rooms/baseroom.c
    
    This is the base room that will be inherited by every room 
    in the Toad-in-Oak area and provides a few basic functions they
    will all need. 

    HISTORY: 2003-08-18 Created by Kcirderf (Based on earlier version)
                
    Copyright: Sean Dunphy (Kcirderf) 2003                    
*/ 

// INCLUSIONS AND DEFINITIONS

#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include "defs.h"

inherit "/d/Calia/std/room_tell_room.c"; 

// FORWARD FUNCTION DEFINITIONS
void force_load_room(string path); 

// FUNCTIONS

/* 
    Name        force_load_room
    Purpose     Forces the rooms specified by path to load so it can 
                be references without somebody having been there first. 
                This function exists to avoid having to remember 
                teleledningsanka and to get around problems with defines. 
    Arguements  The path to the room to be loaded
    Returns     Nothing
*/
void
force_load_room(string path)
{
    path->teleledningsanka(); 
}
    
// ROOM_DEFINITION

void 
create_tio_room()
{
}

public nomask void
create_room()
{

    set_short("A room in Toad-in-Oak"); 
    set_long("A room in Toad-in-Oak\n"); 

    add_prop(ROOM_I_INSIDE, 0); 
    add_prop(ROOM_I_TYPE, ROOM_NORMAL); 

    create_tio_room(); 
}


