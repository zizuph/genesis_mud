/*
 * /d/Calia/central/toad_in_oak/rooms/baseroom.c
 *
 * This is the toad_in_oak baseroom. It contains a few general functions needed
 * in all of the villages rooms. 
 *
 * HISTORY: [99-07-24] Created by Kcirderf 
 *
 * Copyright (C): Kcirderf 1999
 *
 */

// INCLUSIONS AND DEFINITIONS

inherit "/d/Calia/std/room_tell_room"; 

#include <stdproperties.h>
#include "defs.h"

// GLOBAL VARIABLES

object Control_Room = find_object(TOAD_IN_OAK_CONTROL_ROOM); 

// FUNCTIONS

/*
 *  Name:       enter_inv
 *  Purpose:    Registers a creature with the control room when it enters this 
 *              room. 
 *  Arguments:  object entering, object representing last location
 *  Returns:    Nothing
 */ 
void
enter_inv(object ob, object from)
{

    ::enter_inv(ob, from); 

    if (living(ob)) 
    {
        if (ob->toad_in_oak_elf()) 
        {
            Control_Room->register_local(ob); 
        }
        elsif (ob->toad_in_oak_animal())
        {
            Control_Room->register_animal(ob); 
        }
        else
        {
            Control_Room->register_outsider(ob); 
        }
    }

    return; 
}

/*
 *  Name:       leave_inv
 *  Purpose:    Unregisters a creature with the control room when it leaves 
 *              this room.
 *  Arguments:  object leaving, object representing destination
 *  Returns:    Nothing
 */ 
void 
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to); 

    if (living(ob))
    {
        if (ob->toad_in_oak()) 
        {
            Control_Room->unregister_local(ob); 
        }
        else
        {
            Control_Room->unregister_outsider(ob); 
        }

    }

    return;
}


/*
 *  Name:       force_load_room
 *  Purpose:    Forces a room to laod by sending a small invisible object there
 *  Arguments:  file name of room to be loaded
 *  Returns:    The room created
 */ 
object
force_load_room(string file)
{
    object drudge, room = 0; 

    if (! find_object(file))
    {
        drudge = clone_object(DRUDGE);
        drudge -> move(file); 
        room = environment(drudge); 
        drudge->remove_object(); 
    }

    return room;
}

/*  Name:       unregister_room
    Purpose:    unregisters a room from the Control_Room lists. This shoul not
                happen very often. 
    Arguments:  none
    returns:    Nothing
 */
void
unregister_room()
{
    Control_Room->unregister_room(this_object()); 
}

void 
register_room()
{
 
    /*  Before we can register with the Control_Room, we have to make sure it
        exists. */ 
    if (!Control_Room) 
    {
        Control_Room = force_load_room(TOAD_IN_OAK_CONTROL_ROOM); 
    }

    Control_Room->register_room(this_object()); 

    return; 
}

/*  Name:       toad_in_oak()
    Purpose:    Identifies this object as belonging to Toad-in-Oak
    Arguments:  None
    Returns:    1
*/ 
int
toad_in_oak()
{
    return 1; 
}

// ROOM DEFINITION

void
create_tio_room()
{
}

public nomask void
create_room()
{
    register_room(); 

    add_prop(ROOM_I_INSIDE, 0); 
    add_prop(ROOM_I_TYPE, ROOM_NORMAL); 

    create_tio_room(); 
}

public nomask void
remove_object()
{
    unregister_room(); 
}
