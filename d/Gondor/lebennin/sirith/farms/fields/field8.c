/*
 * /d/Gondor/lebennin/sirith/farms/field8.c	
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
	"A hedge rises on the far side of the north ditch, and "+
	"beyond the east ditch runs a narrow track.");

    add_exit("track8", "east", ditch_msg, 3, 1);
    add_exit("track9", "northeast", ditch_msg, 3, 1);

    set_no_exit_msg( ({ "north" }),
	"The hedge blocks your path north.\n");
    set_no_exit_msg( ({ "southeast", "south", "southwest", "west",
	"northwest" }),
	"You wander about the field for a bit.\n");

    add_item( ({ "north ditch", "hedge" }),
	BSN("The hedge appears to enclose a farmstead."));
    add_item( ({ "farm", "building", "buildings", "farmstead" }),
	BSN("The buildings inside the hedge appear to be "+
	    "part of a farm, but you cannot see much from here."));
} /* create_outdoors */
