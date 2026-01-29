/*
 * /d/Gondor/lebennin/sirith/farms/track5.c	
 * track in farm community in southern Lebennin
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
    set_areatype("track");
    set_extraline("Open fields lie beside the track, and "+
	"there are some buildings in the distance to the northwest.");

    add_exit("track6", "north", 0, 2);
    add_exit("field5", "northeast", ditch_msg, 3, 1);
    add_exit("field4", "east", ditch_msg, 3, 1);
    add_exit("field2", "southeast", ditch_msg, 3, 1);
    add_exit("track4", "south", 0, 2);
    add_exit("field3", "west", ditch_msg, 3, 1);
    add_exit("field1", "southwest", ditch_msg, 3, 1);

    set_no_exit_msg( ({ "northwest" }),
	BSN("You wander along the ditch for a bit, then return to "+
	    "the track."));

    /* directions of exits to fields */
    set_trackdir( ({ "east",
	"northeast", "southeast", "west", "southwest" }) );

    add_item( ({ "building", "buildings", "farm", "farmstead" }),
	BSN("The buildings probably are a farmstead, "+
	"but you cannot see details from here."));
} /* create_outdoors */
