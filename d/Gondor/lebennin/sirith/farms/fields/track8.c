/*
 * /d/Gondor/lebennin/sirith/farms/track8.c	
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
    set_extraline("Green fields line the path, and a narrow band "+
	"of trees runs to the southwest. A little to the northwest, "+
	"a hedge encloses a group of buildings.");

    add_exit("track9", "north", 0, 2);
    add_exit("pasture4", "northeast", 0, 2, 1);
    add_exit("field9", "east", ditch_msg, 3, 1);
    add_exit("track3", "southwest", 0, 2);
    add_exit("field8", "west", ditch_msg, 3, 1);

    set_no_exit_msg( ({ "southeast", "south", "northwest" }),
	"You stroll along the edges of the track.\n");

    /* directions of exits to fields */
    set_trackdir( ({ "east", "west" }) );

    add_item( ({ "building", "buildings", "hedge", "farm", "farmstead" }),
	BSN("The small group of buildings is completely circled by a "+
	    "hedge. They probably are a farmstead, but you cannot be "+
	    "sure from here."));
    add_item( ({ "tree", "trees", "woods", "forest" }),
	BSN("A narrow band of trees runs west to east. They "+
	    "do not appear very old; probably they were planted "+
	    "to serve as a windbreak."));
} /* create_outdoors */
