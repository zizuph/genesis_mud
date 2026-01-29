/*
 * /d/Gondor/lebennin/sirith/farms/track3.c	
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
    set_extraline("The track passes through a narrow strip of trees,"+
	" running west to east.");

    add_exit("track4", "north", 0, 2);
    add_exit("track8", "northeast", 0, 2);
    add_exit("track2", "south", 0, 2);

    set_no_exit_msg( ({ "east", "southeast", "west",
	"northwest", "southwest" }),
	BSN("You wander among the trees for a while, then "+
	    "emerge onto the track."));


    /* this is before the cultivated fields start, so redo some
     * default items
     */
    add_item( ({ "fallow field", "fallow fields", "field", "fields" }),
	BSN("There are fields in the distance to the north and "+
	    "south of the trees."));
    add_item( ({ "path", "road", "ground", "grass",
	"narrow track", "grassy track", "track" }),
	BSN("The track gets even narrower as it passes through the trees, "+
	    "and the ankle-high grass shows few signs of traffic."));
    add_item( ({ "signs", "signs of traffic" }),
	"It would seem that few travel this way.\n");
    add_item( ({ "strip of trees", "band of trees", "narrow band of trees",
	"strip", "band", "narrow band", "windbreak",
	"tree", "trees", "woods", "forest" }),
	BSN("A narrow band of trees, running west to east. They "+
	    "do not appear very old; probably they were planted "+
	    "to serve as a windbreak."));
    set_getnames("grass");
    set_getmsg("You pick a stem of grass, but it's nothing "+
	"unusual; you throw it away.");

    add_cmd_item( ({ "windbreak", "trees", "woods" }), ({ "enter" }),
	BSN("You wander among the trees for a while, then "+
	    "emerge onto the track."));

    add_cmd_item( ({ "trees", "tree" }), ({ "climb" }),
	BSN("The trees are not very old, and you do not see any "+
	    "that seem large enough to bear your weight."));

} /* create_outdoors */
