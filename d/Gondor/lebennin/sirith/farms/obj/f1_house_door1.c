/*
 * /d/Gondor/lebennin/sirith/farms/obj/f1_house_door1.c
 *
 * Copyright (C) 1997 by Nancy L. Mintz (Gnadnar)
 * door from farm1/hedgeyard to farm1/house
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
    set_door_id("farm1_house_door");
    set_pass_command( ({"w","west"}) );
    set_door_name( ({ "farmhouse door", "door", "wooden door" }) );
    set_door_desc("A wooden door, stained dark brown, leads west.\n");
    set_open_desc(0);
    set_closed_desc(0);

    set_other_room(SIRITH_FARMS_DIR + "farm1/house");

    set_lock_command("lock");
    set_lock_name("lock");
    set_unlock_command("unlock");

    set_open(0);         /* 1 if open, 0 if closed */
    set_locked(0);       /* 1 if locked, 0 if unlocked */
    set_key("Farm1_House_Key");	/* doesn't exist now, but might someday */
} /* create_door */
