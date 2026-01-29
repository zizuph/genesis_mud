/*
 * /d/Gondor/lebennin/sirith/farms/pasture1.c	
 * field in farm community in southern Lebennin
 *
 * Copyright (C) 1997 by Nancy L. Mintz (Gnadnar)
 *
 */

#pragma strict_types
#include "/d/Gondor/defs.h"
#include "../defs.h"			

inherit "/d/Gondor/lebennin/sirith/farms/outdoors";

public void	create_outdoors();

/*
 * Function name:	create_outdoors
 * Description	:	set up the room
 */
public void
create_outdoors()
{
    set_areatype("pasture");
    set_ditchdir("south");

    add_exit("pasture2", "east", 0, 2, 1);
    add_exit("field6", "south", ditch_msg, 3, 1);
    add_exit("track7", "southeast", 0, 2, 1);

    set_no_exit_msg( ({ "north", "northeast", "southwest", "west",
	"northwest" }),
	"You wander among the flowers and grasses.\n");
} /* create_outdoors */
