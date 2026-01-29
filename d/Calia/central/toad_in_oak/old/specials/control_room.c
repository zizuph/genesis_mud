/*
 * /d/Calia/central/toad_in_oak/specials/control_room.c
 *
 * This room contains functions to control various things in the village of 
 * Toad-in-Oak
 *
 * HISTORY: [99-07-23] Created by Kcirderf 
 *
 * Copyright (C): Kcirderf 1999
 *
 */

// INCLUSIONS AND DEFINITIONS

inherit "/d/Calia/std/room_tell_room"; 

#include <stdproperties.h>
#include "defs.h"

#define DUCK    TOAD_IN_OAK_ANIMALS + "duck" 

// GLOBAL VARIABLES

mapping Registry = ([]);

// FUNCTIONS

/*
 *  Name:       register
 *  Purpose:    add an object to a given array in the registry
 *  Arguments:  name of array to add to, object to add
 *  Returns:    none
 */ 
void 
register(string type, object new_item)
{
    object* items = Registry[type]; 

    if (sizeof(items) == 0 )
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
 *  Name:       unregister
 *  Purpose:    remove an object from a given array in the registry
 *  Arguments:  name of array to remove from , object to remove
 *  Returns:    none
 */ 
void 
unregister(string type, object item)
{
    object* items = Registry[type]; 
    
    if (member_array(item, items) >= 0 )
    {
        items -= ({item}); 
    }
    else
    {    
        items -= ({0}); 
    }

    Registry[type] = items; 
}

/*  Name        count
    Purpose     Returns the number of objects in a array from the registry
    Arguments   Name of array
    Returns     size of array
*/
int
count(string type)
{
    object* items = Registry[type]; 

    return sizeof(items); 
}

/*  Name        random_item
    Purpose     Returns a random object of a given type
    Arguments   string indicating object type (array name)
    Returns     random object
*/ 
object
random_item(string type)
{
    object* items = Registry[type]; 

    return items[random(sizeof(items))]; 
}

// ROOM DEFINITION

void create_room()
{
    set_short("Toad-in-Oak central control room"); 

    set_long("This is the Toad-in-Oak control room. There is nothing to " +
        "see or do here for now.\n"); 
        
    /*  Properties  */ 

    add_prop(ROOM_I_LIGHT, 10); 
    add_prop(ROOM_I_INSIDE, 1); 
    add_prop(ROOM_I_HIDE, 0); 

}
