/*
 * /d/Gondor/lebennin/sirith/farms/obj/f1_smokeh_door1.c
 *
 * Copyright (C) 1997 by Nancy L. Mintz (Gnadnar)
 * door from farm1/northyard to farm1/smokehouse
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
 * Description	:	set up the door
 */
public void
create_door() 
{
    ::create_door();
    set_door_id("farm1_smokehouse_door");
    set_pass_command( ({"n","north"}) );
    set_door_name( ({ "plank door", "heavy door", "heavy plank door", 
	"shed door", "smokehouse door", "door" }) );
    set_door_desc("A heavy plank door leads north.\n");
    set_open_desc(0);
    set_closed_desc(0);

    set_other_room(SIRITH_FARMS_DIR + "farm1/smokehouse");

    set_open(0);         /* 1 if open, 0 if closed */
    set_locked(0);       /* 1 if locked, 0 if unlocked */
} /* create_door */
