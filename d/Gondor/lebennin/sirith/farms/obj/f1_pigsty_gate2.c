/*
 * /d/Gondor/lebennin/sirith/farms/obj/f1_pigsty_gate2.c
 * gate from farm1/pigsty to farm1/southyard
 *
 * Copyright (C) 1997 by Nancy L. Mintz (Gnadnar)
 *
 *
 *    2006.08.29, Toby: Fixed a missing \n.
 */

#pragma strict_types

inherit "/std/door";
#include "../defs.h"

public void	create_door();
public int	open_door(string arg);

/*
 * Function name:	create_door
 * Description	:	set up the gate
 */
public void
create_door() 
{
    ::create_door();
    set_door_name( ({ "wooden gate", "fence gate", "gate" }) );
    set_door_id("pig_gate");
    set_pass_command( ({"n","north"}) );
    set_door_desc("A wooden gate, with a simple latch, leads north.\n");
    set_open_desc(0);
    set_closed_desc(0);

    set_other_room(SIRITH_FARMS_DIR + "farm1/southyard");

    set_open(1);         /* 1 if open, 0 if closed */
    set_locked(0);       /* 1 if locked, 0 if unlocked */
} /* create_door */

/*
 * Function name:	open_door
 * Description	:	intercept standard open_door() so can tell
 *			pigsty that player opened gate (pig may
 *			want to escape)
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 if we understand the arg, 0 otherwise
 */
public int
open_door(string arg)
{
    int rval;

    rval = ::open_door(arg);
    if (rval)
    {
	ENV()->opened_gate(TP);
    }
    return rval;
} /* open door */
