/*
 * /d/Gondor/lebennin/sirith/farms/obj/f1_pigsty_gate1.c
 * gate from farm1/southyard to farm1/pigsty
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
    set_pass_command( ({"s","south"}) );
    set_door_desc("A wooden gate, with a simple latch, leads south.\n");
    set_open_desc(0);
    set_closed_desc(0);

    set_other_room(SIRITH_FARMS_DIR + "farm1/pigsty");

    set_open(1);         /* 1 if open, 0 if closed */
    set_locked(0);       /* 1 if locked, 0 if unlocked */
} /* create_door */
