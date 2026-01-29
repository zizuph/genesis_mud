/*
 * /d/Gondor/lebennin/sirith/farms/pasture5.c	
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
    set_extraline("A mixture of grasses, dotted with wildflowers, covers "+
	"the pasture. A little to the southwest is a small group of "+
	"buildings, enclosed by a hedge.");

    add_exit("pasture6", "east", 0, 2, 1);
    add_exit("track9", "south", 0, 2, 1);
    add_exit("pasture4", "southeast", 0, 2, 1);

    set_no_exit_msg( ({ "north", "northeast", "southwest", "west",
	"northwest" }),
	"You wander among the grasses.\n");

    add_item( ({ "hedge", "group", "group of buildings",
    		 "farm", "building", "buildings", "farmstead" }),
	BSN("The buildings inside the hedge appear to be "+
	    "a small farm, but you cannot see much from here."));
} /* create_outdoors */
