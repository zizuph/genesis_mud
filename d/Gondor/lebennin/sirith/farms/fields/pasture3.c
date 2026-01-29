/*
 * /d/Gondor/lebennin/sirith/farms/pasture3.c	
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

    add_exit("pasture2", "west", 0, 2, 1);
    add_exit("field7", "south", ditch_msg, 3, 1);
    add_exit("track7", "southwest", 0, 2, 1);

    set_no_exit_msg( ({ "north", "northeast", "east", "southeast",
	"northwest" }),
	"You roam the edges of the pasture.\n");
} /* create_outdoors */
