/*
 * /d/Calia/central/toad_in_oak/specials/control_room.c
 *
 * This room contains functions to control and monitor various
 * aspects of the Toad-in-Oak project
 * 
 * HISTORY: 2003-05-10 Created by Kcirderf (based on an earlier version)
 *
 * Copyright: Sean Dunphy (Kcirderf) 2003
 */

inherit "/d/Calia/std/room_tell_room.c";

#include <stdproperties.h>
#include "defs.h"

// GLObal VARIABLES

mapping Registry = ({});

// FUNCTIONS

/* 
 * Name:        Register
 * Purpose:     add an object of a given type to the registry 
 * Arguments:   type - The type of object being added
 *              object - The object being added
 * Returns:     Nothing
 */ 
void
register(string type, object new_item)
{
    object* items = Registry[type]; 

    if (sizeof(items) == 0)     
    {
        Registry[type] = ({new_item}); 
    }
    else
    {
        if (member_array(new_item, items) == -1)
        {
            items += ({new_item}); 
            Registry[type] = items; 
        }
    }
}

/* 
 *  Name:       Unregister
 *  Purpose:    remove an object of a given type from the registry 
 *  Arguments:  type - the type of object being removed
 *              object - the object being removed
 *  Returns:    Nothing
 */
void
unregister(string type, object item)
{
    object* items = Registry[type]; 
    
    if (member_array(item, items) >= 0)
    {
        items -= ({item}); 
    }

    if (sizeof(items) == 0) 
    {
        m_delete(Registry, type);
    }
    else
    {
        Registry[type] = items;
    }
}

// ROOM DEFINITION

void
create_room()
{
    set_short( "Toad-in-Oak Central Control Room"); 
    set_long("This is the Toad-in-Oak control room. There is nothing to " +
        "see or do here for now.\n"); 
    add_prop(ROOM_I_LIGHT, 10); 
    add_prop(ROOM_I_INSIDE, 1); 
    add_prop(ROOM_I_HIDE, 0); 

}

