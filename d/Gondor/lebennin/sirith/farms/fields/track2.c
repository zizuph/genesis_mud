/*
 * /d/Gondor/lebennin/sirith/farms/track2.c	
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
    set_noitems(1);
    set_areatype("track");
    set_extraline("Open fields stretch east and west beside the track.");

    add_exit("track3", "north", 0, 2);
    add_exit("track1", "southeast", 0, 2);

    set_no_exit_msg( ({ "northeast", "east", "south", "southwest",
	"west", "northwest" }),
	BSN("You walk through the fields for a while before returning "+
	    "to the track."));


    /* this is before the cultivated fields start, so redo some
     * default items
     */
    add_item( ({ "fallow field", "fallow fields", "field", "fields" }),
	"The fields appear to be lying fallow.\n");
    add_item( ({ "path", "road", "ground", "grass",
	"narrow track", "grassy track", "track" }),
	"The grassy track shows few signs of traffic.\n");
    add_item( ({ "signs", "signs of traffic" }),
	"It would seem that few travel this way.\n");
    set_getnames("grass");
    set_getmsg("You pick a stalk of grass, but it's not "+
	"very interesting; you throw it away.");
} /* create_outdoors */
