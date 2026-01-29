/*
 * /d/Gondor/lebennin/sirith/farms/obj/f2_house_door1.c
 *
 * Copyright (C) 1997 by Nancy L. Mintz (Gnadnar)
 * door from farm2/westyard to farm2/house
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
    set_door_id("farm2_house_door");
    set_pass_command( ({"s","south"}) );
    set_door_name( ({ "farmhouse door", "door",
    	"simple door", "wooden door", "simple wooden door" }) );
    set_door_desc("A simple wooden door leads south.\n");
    set_open_desc(0);
    set_closed_desc(0);

    set_other_room(SIRITH_FARMS_DIR + "farm2/house");

    set_lock_command("lock");
    set_lock_name("lock");
    set_unlock_command("unlock");

    set_open(1);         /* 1 if open, 0 if closed */
    set_locked(0);       /* 1 if locked, 0 if unlocked */
    set_key("Farm2_House_Key");	/* doesn't exist now, but might someday */
} /* create_door */
