/*
 * /d/Gondor/lebennin/sirith/farms/obj/f1_yard_gate1.c
 *
 * Copyright (C) 1997 by Nancy L. Mintz (Gnadnar)
 * gate from track6 to farm1/eastyard
 *
 *
 *    2006.08.29, Toby: Fixed a missing \n.
 */

#pragma strict_types

inherit "/std/door";

#include "../defs.h"

public void	create_door();


/*
 * Function name:	create_door
 * Description	:	set up the gate
 */
public void
create_door() 
{
    ::create_door();
    set_door_name( ({ "farmstead gate", "gate", "farmyard gate",
	"heavy gate", "bank gate" }) );
    set_door_id("farm1_gate");
    set_pass_command( ({"w","west"}) );
    set_door_desc("The farmstead gate is made of heavy timbers "
		+ "and leads west.\n");
    set_open_desc(0);
    set_closed_desc(0);

    set_other_room(SIRITH_FARMS_DIR + "farm1/eastyard");

    set_open(0);         /* 1 if open, 0 if closed */
    set_locked(0);       /* 1 if locked, 0 if unlocked */
} /* create_door */
