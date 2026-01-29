/*
 * /d/Gondor/lebennin/sirith/room.c
 *
 * Copyright (C) 1997 by Nancy L. Mintz (Gnadnar)
 *
 * a general purpose room (not restricted to farms).
 * inherits /d/Gondor/std/room
 * gives improved door handling. the standard door does not
 *	   say whether it's open or closed when you look at it,
 *	   which seems wrong. it also doesn't id to anything
 *	   which makes it hard to find. this room adds open/closed
 *	   state to the door desc, and has the door id to SIRITH_DOOR.
 *	   LIMITATION: only one door per room (at least for now).
 */
	

#pragma strict_types

#include <macros.h>			/* for VBFC_ME	*/
#include "/d/Gondor/defs.h"
#include "defs.h"

inherit "/d/Gondor/std/room";

static int	Doors_are_plural;	/* so we use the right pronouns	*/

varargs public object	set_door(string path, int are_plural);
public string		look_door();


/*
 * Function name:	create_sirith
 * Description  :	redefine this to create sirith rooms
 */
public void
create_sirith()
{
} /* create_sirith */


/*
 * Function name:	create_gondor
 * Description  :	constructor
 */
nomask void
create_gondor()
{
    create_sirith();
} /* create_gondor */


/*
 * Function name:	set_door
 * Description	:	set up a door/gate for this room
 * Arguments	:	string path -- the door to clone
 *			int are_plural -- (optional arg) if non-zero,
 *					 doors are plural
 * Returns	:	the door object
 *
 * default door doesn't tell you whether it's open or closed when you
 * look at it. default door also doesn't appear to id to "door" or any
 * of its names, so it's hard to find again. this seems wrongheaded to
 * me, so i mess with it a little ...
 *
 */
varargs public object
set_door(string path, int are_plural = 0)
{
    object	door;
    string	*doornames;

    if (strlen(path) &&
	objectp(door = clone_object(path)))
    {
	door->add_name(SIRITH_DOOR);
	door->move(TO);
	doornames = door->query_door_name();
	remove_item(doornames);
	add_item(doornames, VBFC_ME("look_door"));
	Doors_are_plural = are_plural;
    }
    return door;
} /* set_door */


/*
 * Function name:	look_door
 * Description	:	VBFC for door/gate
 * Returns	:	string -- desc of door/gate
 */
public string
look_door()
{
    object door;
    if (objectp(door = present(SIRITH_DOOR)))
    {
	return BSN(door->query_door_desc() + 
	    ( !Doors_are_plural ? " It is " : " They are " )+
	    ( door->query_open() ? "open." : "closed." ));
    }

    /* wonder where our door/gate went ... */
    if ( !Doors_are_plural )
    {
	return "It looks fairly sturdy.\n";
    }
    return "They look fairly sturdy.\n";
} /* look_door */
