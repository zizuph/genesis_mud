/*
 * /d/Gondor/lebennin/sirith/farms/field1.c	
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
    set_areatype("field");
    set_trackdir("east");

    add_exit("field3", "north", ditch_msg, 3, 1);
    add_exit("track5", "northeast", ditch_msg, 3, 1);
    add_exit("track4", "east", ditch_msg, 3, 1);

    set_no_exit_msg( ({ "southeast", "south", "southwest", "west",
	"northwest" }),
	"You wander along the edges of the field.\n");
} /* create_outdoors */
