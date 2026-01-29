/*
 * /d/Gondor/river/anduin/lorien2rauros/river14w.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * in the downs, ~20 miles downstream of the day 6 campsite, 
 * approaching the emyn muil
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
public string	scenery_msgs(object ob, string vb, string dir);


/*
 * Function name:	create_anduin_onwater
 * Description	:	set up the room
 */
public void
create_anduin_onwater()
{
    add_prop(OBJ_S_WIZINFO,
	BSN("in the downs, ~20 miles downstream of the day 6 campsite, "+
	    "about 275 miles downstream from the silverlode, "+
	    "approaching the emyn muil."));
    set_short("on the west side of the River Anduin");

    /* use tod_descs to append time-of-day descriptions to long
     * and to handle sky items
     */
    set_tod_long("The Great River splashes over occasional "+
	"gravel-shoals as it flows south past rolling downs on "+
	"either shore.");

    set_tod_landname("the Downs");
    set_tod_landtype("river");
    set_tod_prependshort(1);
    set_long(tod_descs);
    add_item( ({ "sky", "sun", "moon", "star", "stars" }), tod_descs );

    set_watertype("river");
    set_watername("River Anduin");
    set_waterrefs( ({ "great river", "waters", "water", "river", "anduin",
	"river anduin", "anduin river" }) );
    set_downstreamdir( ({ "south", "southeast" }) );
    set_upstreamdir("north");
    set_currentstr( ({ 6, 6 }) ); /* rapid */ 
    set_depth(610); /* 20 feet */
    set_rock_density(SCATTERED_ROCKS + 1);

    add_exit("river13w", "north");
    set_distance("north", 20);
    add_exit("river14e", "east");
    add_exit("river15w", "south");
    set_distance("south", 25);
    add_exit("river15e", "southeast");
    set_distance("southeast", 25);
    add_exit("riverbottom14w", "down");
    /* no shore rooms for now */

    add_item( ({ "great river", "waters", "water", "river anduin",
	"anduin river", "anduin", "river" }),
	BSN("The waters swirl over scattered shoals."));
    add_item( ({  "shore", "shores", "river bank", "river banks",
	"bank", "banks" }),
	BSN("High, rolling downs rise on either side of the Anduin."));
    add_item( ({ "eastern shore", "eastern bank", "east shore",
	"east bank" }),
	BSN("Beyond narrow beaches on the far shore, high downs extend "+
	    "to the horizon."));
    add_item( ({ "western shore", "western bank", "west shore",
	"west bank", }),
	BSN("Rolling, treeless plains stretch away west."));
    add_item( ({ "gravel", "shoals", "gravel-shoals" }),
	BSN("Long shoals lie just below the water surface."));
    add_item( ({ "beach", "long beach", "stony beach", "long beaches",
	"stony beaches", "beaches" }),
	BSN("Narrow, stony beaches lie along the eastern shore."));
    add_item( ({ "hill", "hills", "plain", "plains", "land", "down", "downs",
	"wold", "wolds", }),
	BSN("Chalky hills of withered crass extend away from the river."));
    add_item( ({ "turf", "grass" }),
	BSN("Sere grass covers the downs."));
} /* create_anduin_onwater */


/*
 * Function name:	scenery_msgs
 * Description	:	mask parent to give a "the banks rise" msg
 *			if people or boats are going downstream.
 * Arguments	:	object ob -- who/what is moving
 *			string vb -- "swim", "wade", "row", "dive", "wash"
 *			string dir -- the direction of movement
 */
public string
scenery_msgs(object ob, string vb, string dir)
{
    string desc;

    if (dir == "south" ||
	dir == "southeast" ||
	dir == "downstream")
    {
	desc = BSN("As you travel downstream, the banks begin to rise "+
	           "and the river grows more rapid.");
    }
    else
    {
	desc = "";
    }
    return desc;
} /* scenery_msgs */
