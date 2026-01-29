/*
 * /d/Gondor/lebennin/sirith/farms/field2.c	
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
    set_trackdir("west");

    add_exit("field4", "north", ditch_msg, 3, 1);
    add_exit("track5", "northwest", ditch_msg, 3, 1);
    add_exit("track4", "west", ditch_msg, 3, 1);

    set_no_exit_msg( ({ "northeast", "east", "southeast", "south",
	"southwest" }),
	"You stroll about the field.\n");
} /* create_outdoors */
