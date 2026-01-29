/*
 * /d/Gondor/lebennin/sirith/farms/field4.c	
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

    add_exit("field5", "north", ditch_msg, 3, 1);
    add_exit("field2", "south", ditch_msg, 3, 1);
    add_exit("track4", "southwest", ditch_msg, 3, 1);
    add_exit("track5", "west", ditch_msg, 3, 1);
    add_exit("track6", "northwest", ditch_msg, 3, 1);

    set_no_exit_msg( ({ "northeast", "east", "southeast" }),
	"You stroll along the field's perimeter.\n");
} /* create_outdoors */
