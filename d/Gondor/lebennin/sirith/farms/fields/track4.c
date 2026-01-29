/*
 * /d/Gondor/lebennin/sirith/farms/track4.c	
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
    set_extraline("Cultivated fields stretch away from the track on "+
	"either side, and a narrow band of trees cuts across the track "+
	"to the south.");

    add_exit("track5", "north", 0, 2);
    add_exit("field4", "northeast", ditch_msg, 3, 1);
    add_exit("field2", "east", ditch_msg, 3, 1);
    add_exit("track3", "south", 0, 2);
    add_exit("field1", "west", ditch_msg, 3, 1);
    add_exit("field3", "northwest", ditch_msg, 3, 1);

    set_no_exit_msg( ({ "southeast", "southwest" }),
	BSN("You wander along the edges of the woods, then "+
	    "return to the track."));

    /* directions of exits to fields */
    set_trackdir( ({ "east", "northeast", "west", "northwest" }) );

    add_item( ({ "tree", "trees", "woods", "forest" }),
	BSN("A narrow band of trees, running west to east. They "+
	    "do not appear very old; probably they were planted "+
	    "to serve as a windbreak."));
} /* create_outdoors */
