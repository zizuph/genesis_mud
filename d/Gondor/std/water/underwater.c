/*
 * /d/Gondor/std/water/underwater.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/water/water_room";

#include <macros.h>		/* for QCTNAME			*/
#include <composite.h>		/* for COMPOSITE_WORDS          */
#include <stdproperties.h>	/* for ROOM_I_TYPE, etc		*/
#include "/d/Gondor/defs.h"	/* always ...			*/

#include "underwater.h"


/* prototypes */
public void		create_underwater();
nomask void		create_water_room();
public void		enter_inv(object ob, object from);
public void		leave_inv(object ob, object dest);
public int		drink_water(string str);
public void		drink_message(string from);


/*
 * Function name:	create_underwater
 * Description	:	creator for underwater rooms
 * Configure your room here.
 */
public void
create_underwater()
{
} /* create_underwater */

/*
 * Function name:	create_water_room
 * Description	:	water_room creator
 */
nomask void
create_water_room()
{
    int s;
    add_prop(ROOM_I_TYPE, ROOM_UNDER_WATER);
    create_underwater();
    s = sizeof(Waterrefs);
    while (s-- > 0)
    {
	try_item(Waterrefs[s], "The water surrounds you.\n");
    }
} /* create_water_room */


/*
 * Function name:	enter_inv
 * Description	:	give players object to monitor breath,
 *			set alarms to float or sink entering objects
 * Arguments	:	object ob -- the object that enters
 *			object from -- where it came from
 */
public void
enter_inv(object ob, object from)
{
    if (interactive(ob) &&
	!present(BREATH_OBJ_NAME, ob))
    {
	clone_object(BREATH_OBJ)->move(ob);
    }
    ::enter_inv(ob, from);
} /* enter_inv */


/* 
 * Function name:	leave_inv
 * Description	:	remove any breath objects
 * Arguments	:	object ob -- the object that leaves
 *			object dest -- where it is going
 */
public void
leave_inv(object ob, object dest)
{
    object breathob;

    ::leave_inv(ob, dest);

    if (interactive(ob) &&
	objectp(breathob = present(BREATH_OBJ_NAME, ob)) &&
	(!objectp(dest) ||
         dest->query_prop(ROOM_I_TYPE) != ROOM_UNDER_WATER))
    {
	breathob->remove_object();
    }
} /* leave_inv */


/* 
 * Function name:	drink_water
 * Description	:	mask parent so can just "drink water" when
 *			are underwater
 * Arguments	:	string str -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 */
public int
drink_water(string str)
{
    if (str == "water")
    {
	str = "water from "+query_drink_from()[0];
    }
    return ::drink_water(str);
} /* drink_water */

/* 
 * Function name:	drink_message
 * Description	:	mask parent so we don't "drink water from water"
 * Arguments	:	string from -- the water source
 */
public void
drink_message(string from)
{
    if (from != "water")
    {
	write("You drink some water from the "+from+".\n"
           +  "You feel refreshed.\n");
	say(QCTNAME(TP) + " drinks some water from the "+from+".\n");
    }
    else
    {
	write("You drink some water.\nYou feel refreshed.\n");
	say(QCTNAME(TP) + " drinks some water.\n");
    }
} /* drink_message */


/*
 * Function name:	unq_no_move
 * Description	:	mask parent so player sees a "swim" failure msg
 * Arguments	:	string arg -- whatever the player typed (not used)
 * Returns	:	0 (msg written via notify_fail)
 */
public int
unq_no_move(string arg)
{
    string	vb = QVB;

    /* If there is a no-exit message, pass to original routine. */
    if (query_no_exit_msg(vb))
    {
    	return ::unq_no_move(arg);
    }

    if (vb != "down")
    {
	notify_fail("You cannot swim "+vb+".\n");
    }
    else
    {
	notify_fail("You cannot dive further.\n");
    }
    return 0;
} /* unq_no_move */
