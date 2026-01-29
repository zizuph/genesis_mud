/*
 * /d/Gondor/river/anduin/carrock2lorien/river08.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * 205 miles south of the Carrock
 *
 */

#pragma strict_types

inherit "/d/Gondor/river/anduin/anduin_onwater";
inherit "/d/Gondor/common/lib/tod_descs";

#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/std/water/onwater.h"
#include "../anduin.h"

/* prototypes */
public void	create_anduin_onwater();
public void	reset_room();
public string	exa_herd(string arg);

static int	Herd_here;


/*
 * Function name:	create_anduin_onwater
 * Description	:	set up the room
 */
public void
create_anduin_onwater()
{
    add_prop(OBJ_S_WIZINFO,
	"205 miles south of the Carrock.\n");
    set_short("on the River Anduin");

    /* use tod_descs to append time-of-day descriptions to long
     * and to handle sky items
     */
    set_tod_long(
	"The river bends from the north towards the southwest, "+
	"rolling past wide plains of tall grass.");
    set_tod_landname("the vale of Anduin");	/* XXX */
    set_tod_landtype("river");
    set_tod_prependshort(1);
    set_long(tod_descs);
    add_item( ({ "sky", "sun", "moon", "star", "stars" }), tod_descs );

    /* set up water stuff */
    set_watertype("river");
    set_watername("River Anduin");
    set_waterrefs( ({ "great river", "waters", "water", "river", "anduin",
	"river anduin", "anduin river" }) );
    set_upstreamdir("north");
    set_downstreamdir("southwest");
    set_currentstr(5);	/* strong */
    set_depth(1524); /* 50 feet */
    /* no rocks */

    add_exit("river07", "north");
    set_distance("north", 30);
    add_exit("river09", "southwest");
    set_distance("southwest", 25);
    add_exit("riverbottom08", "down");
    /* no shore rooms for now */

    add_item( ({ "great river", "waters", "water", "river anduin",
	"anduin river", "anduin", "river" }),
	BSN("The Anduin is a mighty river, wide and fast-moving. "+
	    "Its waters are dark and appear quite deep."));
    add_item( ({ "land", "view", "vale", "inland", "river bank",
	"river banks", "bank", "banks", "shore", "shores", }),
	BSN("Smooth expanses of tall grass roll away "+
	    "from the river on either shore."));
    add_item( ({ "eastern bank", "east bank", "eastern shore",
	"east shore", }),
	BSN("Open grassland stretches east from the river. Far in "+
	    "the distance, a dark line runs along the horizon."));
    add_item( ({ "eastern horizon", "east horizon", "horizon",
	"dark line", "line", }),
	BSN("The dark line on the east horizon is all that "+
	    "can be seen of Mirkwood."));
    add_item( ({ "vast forest", "forest", "mirkwood" }),
	BSN("All that can be seen of Mirkwood is a dark line "+
	    "on the east horizon."));
    add_item( ({ "wide plains", "plains", "wide plain",
	"plain", "grassland", "grasslands", }),
	BSN("Tall green and gold grasses ripple away from the river."));
    add_item( ({ "west horizon", "western horizon", }),
	BSN("To the west is grass, all the way to to the horizon."));
    add_item( ({  "green and gold sea", "sea", "rippling grass",
	"rippling grasses", "tall grass", "tall grasses", "grass",
	"grass", "grasses", }),
	&exa_herd("grass"));
    add_item( ({ "western bank", "west bank", "western shore",
	"west shore",  }),
	&exa_herd("shore"));
    add_item( ({ "branch", "branches", "dead tree", "tree", }),
	&exa_herd("branch"));
    add_item( ({ "very tip", "tip", "tip of horns", "pair",
	"pair of horns", "horn", "horns", }),
	&exa_herd("horn"));
    add_item( ({ "animal", "herd", "herd of deer", "deer", }),
	&exa_herd("deer"));

    /* reset the room so that herd might move every 30 minutes or so
     * ("sman /std/object enable_reset" for more info)
     */
    enable_reset(200);
    reset_room();
} /* create_anduin_onwater */


/*
 * Function name:	reset_room
 * Description	:	change state of herd
 */
public void
reset_room()
{
    ::reset_room();

    /* 50-50 chance it changes */
    if (!random(2))
    {
	return;
    }
    if (Herd_here)
    {
	tell_room(TO,
	    BSN("Suddenly a herd of beige-furred white-tailed deer leaps "+
	   	"from its resting place in the grass and sprints "+
		"away west."));
	Herd_here = 0;
    }
    else
    {
	/* lets pretend they were sleeping in the grass all along,
	 * but only just now lift their heads enough to become
	 * noticeable. in other words, i can't think of a good
	 * one-fell-swoop msg for deer arriving ...
	 */
	Herd_here = 1;
    }
} /* reset_room */


/*
 * Function name:	exa_herd
 * Description	:	VBFC for grass/west shore/branches/herd/...
 * Arguments	:	string arg -- what was exa'd
 * Returns	:	string -- the description
 */
public string
exa_herd(string arg)
{
    string	desc;
    switch (arg)
    {
    case "grass":
	desc = "The tall grasses ripple in the slightest breeze.";
	if (Herd_here)
	{
	    desc += " Along the west shore, the branches of a "+
		"dead tree stick up out of the grass.";
	}
	break;
    case "shore":
	desc = "Tall grasses flow west from the river like a green "+
	    "and gold sea.";
	if (Herd_here)
	{
	    desc += " Branches of dead trees stick up out of the grass.";
	}
	break;
    case "branch":
	if (Herd_here)
	{
	    desc = "The branches are oddly shaped -- they almost look "+
		"like horns.";
	}
	break;
    case "horn":
	if (Herd_here)
	{
	    desc = "Just visible above the tall grass are a pair "+
	        "of horns.";
	}
	break;
    case "deer":
	if (Herd_here)
	{
	    desc = "All that can be seen is the very tip of a pair "+
		"horns.";
	}
	break;
    }
    if (!strlen(desc))
    {
	desc = "You find no "+query_exa_arg()+".";
    }
    return BSN(desc);
} /* exa_herd */
