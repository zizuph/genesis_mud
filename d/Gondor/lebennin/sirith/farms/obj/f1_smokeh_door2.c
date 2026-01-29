/*
 * /d/Gondor/lebennin/sirith/farms/obj/f1_smokeh_door2.c
 *
 * Copyright (C) 1997 by Nancy L. Mintz (Gnadnar)
 * door from farm1/smokehouse to farm1/northyard 
 *
 *
 *    2006.08.29, Toby: Fixed a missing \n.
 */

#pragma strict_types

inherit "/std/door";

#include <stdproperties.h>	/* for ROOM_I_LIGHT */
#include "../defs.h"

public void	create_door();
public void	do_open_door(string mess);
public void	do_close_door(string mess);


/*
 * Function name:	create_door
 * Description	:	set up the door
 */
public void
create_door() 
{
    ::create_door();
    set_door_id("farm1_smokehouse_door");
    set_pass_command( ({"s","south"}) );
    set_door_name( ({ "plank door", "heavy door", "heavy plank door", 
	"shed door", "smokehouse door", "door" }) );
    set_door_desc("A heavy plank door leads south.\n");
    set_short(0);	/* must be done after set_door_id() */
    set_open_desc("An open door leads south.\n");
    set_closed_desc("A closed door leads south.\n");

    set_other_room(SIRITH_FARMS_DIR + "farm1/northyard");

    set_open(0);         /* 1 if open, 0 if closed */
    set_locked(0);       /* 1 if locked, 0 if unlocked */
} /* create_door */


/*
 * Function name:	do_open_door
 * Description	:	mask parent so we update light levels
 * Arguments	:	string mess -- the "door opens" message
 */
void
do_open_door(string mess)
{
    object	env = ENV();
    ::do_open_door(mess);
    env->add_prop(ROOM_I_LIGHT, (env->query_prop(ROOM_I_LIGHT) + 1));
} /* do_open_door */

/*
 * Function name:	do_close_door
 * Description	:	mask parent so we update light levels
 * Arguments	:	string mess -- the "door closes" message
 */
void
do_close_door(string mess)
{
    object	env = ENV();
    ::do_close_door(mess);
    env->add_prop(ROOM_I_LIGHT, (env->query_prop(ROOM_I_LIGHT) - 1));
} /* do_close_door */
