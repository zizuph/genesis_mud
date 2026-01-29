/*
 * /d/Gondor/lebennin/sirith/farms/field3.c	
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
    set_areacrop("");
    set_extraline("A thriving crop of "+query_areacrop()+
	" covers the field, which is enclosed by fairly deep ditches. "+
	"Beyond the east ditch runs a narrow track, and a turf bank rises "+
	"on the far side of the ditch to the north.");

    add_exit("track6", "northeast", ditch_msg, 3, 1);
    add_exit("track5", "east", ditch_msg, 3, 1);
    add_exit("track4", "southeast", ditch_msg, 3, 1);
    add_exit("field1", "south", ditch_msg, 3, 1);

    set_no_exit_msg( ({ "north" }),
	"The turf bank blocks your progress north.\n");
    set_no_exit_msg( ({ "southwest", "west", "northwest" }),
	"You wander along the edges of the field.\n");

    add_item( ({ "north ditch", "turf bank", "turf", "bank" }),
	"The turf bank appears to enclose a farmstead.\n");
    add_item( ({ "farm", "building", "buildings", "farmstead" }),
	BSN("The buildings inside the turf bank appear to be "+
	    "part of a farm, but you cannot see much from here."));
} /* create_outdoors */
