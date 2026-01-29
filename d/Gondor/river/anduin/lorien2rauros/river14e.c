/*
 * /d/Gondor/river/anduin/lorien2rauros/river14e.c
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
    set_short("on the east side of the River Anduin");

    /* use tod_descs to append time-of-day descriptions to long
     * and to handle sky items
     */
    set_tod_long("The wide waters flow swiftly south, "+
	"swirling over scattered gravel-shoals and skirting rocky "+
	"beaches along the eastern shore.");

    set_tod_landname("the Downs");
    set_tod_landtype("river");
    set_tod_prependshort(1);
    set_long(tod_descs);
    add_item( ({ "sky", "sun", "moon", "star", "stars" }), tod_descs );

    set_watertype("river");
    set_watername("River Anduin");
    set_waterrefs( ({ "great river", "waters", "water", "river", "anduin",
	"river anduin", "anduin river" }) );
    set_downstreamdir( ({ "south", "southwest" }) );
    set_upstreamdir("north");
    set_currentstr( ({ 6, 6 }) ); /* rapid */ 
    set_depth(610); /* 20 feet */
    set_rock_density(SCATTERED_ROCKS + 1);

    add_exit("river15e", "south");
    set_distance("south", 25);
    add_exit("river15w", "southwest");
    set_distance("southwest", 25);
    add_exit("river13e", "north");
    set_distance("north", 20);
    add_exit("river14w", "west");
    add_exit("riverbottom14e", "down");
    add_exit("beach14e", "east");

    add_item( ({ "great river", "waters", "water", "river anduin",
	"anduin river", "anduin", "river" }),
	BSN("The Anduin is wide, swift, and dotted with shoals."));
    add_item( ({  "shore", "shores", "river bank", "river banks",
	"bank", "banks" }),
	BSN("High, rolling downs rise on either side of the Anduin."));
    add_item( ({ "eastern shore", "eastern bank", "east shore",
	"east bank" }),
	BSN("Narrow beaches line the eastern shore, and beyond them "+
	    "rise high downs."));
    add_item( ({ "western shore", "western bank", "west shore",
	"west bank", }),
	BSN("On the far side of the river, the land rises into "+
	    "bare hills."));
    add_item( ({ "gravel", "shoals", "gravel-shoals" }),
	BSN("Scattered gravel-shoals roil the waters."));
    add_item( ({ "bare stone", "stone", "strips", "edge", "beach",
	"long beach", "stony beach", "long beaches", "stony beaches",
	"beaches" }),
	BSN("The beaches are mere strips of bare stone at the river's "+
	    "edge."));
    add_item( ({ "hill", "hills", "plain", "plains", "land", "down", "downs",
	"wold", "wolds", }),
	BSN("Rolling, treeless expanses of withered grass stretch away "+
	    "on either side of the river."));
    add_item( ({ "turf", "grass" }),
	BSN("The grass is dry and short."));
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
	dir == "southwest" ||
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
