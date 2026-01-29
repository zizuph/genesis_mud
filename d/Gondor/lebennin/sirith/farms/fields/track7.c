/*
 * /d/Gondor/lebennin/sirith/farms/track7.c	
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
    set_extraline("Cultivated fields run on either side of the track "+
	"and open pasture extends north. There are some buildings in the "+
	"distance to the southwest.");

    add_exit("pasture2", "north", 0, 2, 1);
    add_exit("pasture3", "northeast", 0, 2, 1);
    add_exit("field7", "east", ditch_msg, 3, 1);
    add_exit("field5", "southeast", ditch_msg, 3, 1);
    add_exit("track6", "south", 0, 2);
    add_exit("field6", "west", ditch_msg, 3, 1);
    add_exit("pasture1", "northwest", 0, 2, 1);

    set_no_exit_msg( ({ "southwest" }),
	"You wander along the ditch for a bit.\n");

    /* directions of exits to fields */
    set_trackdir( ({ "east", "southeast", "west" }) );

    add_item( ({ "building", "buildings", "farm", "farmstead" }),
	BSN("The buildings probably are a farmstead, "+
	"but they are too far away to see details."));
    add_item( ({ "pasture", "pastures", "open pasture", "open pastures" }),
	"An open, grassy pasture is to the north.\n");
} /* create_outdoors */
