/*
 * /d/Gondor/lebennin/sirith/farms/field6.c	
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
    set_extraline("The field is circled on all sides by a fairly "+
    	"deep ditch, and appears to be sown with "+query_areacrop()+
	". A grassy track runs along the edge of the field beyond the "+
	"east ditch, and a turf bank encloses some buildings "+
	"to the south.");

    add_exit("pasture1", "north", ditch_msg, 3, 1);
    add_exit("pasture2", "northeast", ditch_msg, 3, 1);
    add_exit("track7", "east", ditch_msg, 3, 1);
    add_exit("track6", "southeast", ditch_msg, 3, 1);

    set_no_exit_msg( ({ "south" }),
	"The turf bank blocks your progress south.\n");
    set_no_exit_msg( ({ "southwest", "west", "northwest" }),
	"You roam the edges of the field.\n");

    add_item( ({ "south ditch", "turf bank", "turf", "bank" }),
	BSN("On the far side of the south ditch, a turf bank "+
	    "rises around several buildings."));
    add_item( ({ "farm", "building", "buildings", "farmstead" }),
	BSN("The buildings inside the turf bank appear to be "+
	    "part of a farm, but you cannot see much from here."));
} /* create_outdoors */
