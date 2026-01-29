/*
 * /d/Gondor/river/anduin/lorien2rauros/river11.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * ~20 miles downstream of the day 5 campsite, in the south undeep
 * at the southern edge of the brown lands.
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
	BSN("~20 miles downstream of the day 5 campsite, at the "+
	    "southern edge of the brown lands, about "+
	    "220 miles downstream from the silverlode."));
    set_short("on the River Anduin");

    /* use tod_descs to append time-of-day descriptions to long
     * and to handle sky items
     */
    set_tod_long(
	"The Great River flows from northeast to southwest across "+
	"the shallow valley of the South Undeep.");
    set_tod_landname("the South Undeep");
    set_tod_landtype("river");
    set_tod_prependshort(1);
    set_long(tod_descs);
    add_item( ({ "sky", "sun", "moon", "star", "stars" }), tod_descs );


    set_watertype("river");
    set_watername("River Anduin");
    set_waterrefs( ({ "great river", "waters", "water", "river", "anduin",
	"river anduin", "anduin river" }) );
    set_downstreamdir("southwest");
    set_upstreamdir("northeast");
    set_currentstr(5);	/* strong */
    set_depth(1524); /* 50 feet */
    /* no rocks */

    add_exit("river10", "northeast");
    set_distance("northeast", 20);
    add_exit("river12", "southwest");
    set_distance("southwest", 33);
    add_exit("riverbottom11", "down");
    /* no shore rooms for now */

    add_item( ({ "great river", "waters", "water", "river anduin",
	"anduin river", "anduin", "river" }),
	BSN("The Anduin widens slightly as it flows across the Undeep."));
    add_item( ({ "eastern shore", "eastern bank", "western shore",
	"western bank", "east shore", "east bank", "west shore",
	"west bank", "shore", "shores", "river bank", "river banks",
	"bank", "banks", "valley",
	"valleys", "south undeep", "undeep" }),
	BSN("The gentle valley of the South Undeep stretches "+
	    "away from either shore."));
} /* create_anduin_onwater */


/*
 * Function name:	scenery_msgs
 * Description	:	mask parent to give a "the river bends" msg
 *			if people or boats are going downstream.
 * Arguments	:	object ob -- who/what is moving
 *			string vb -- the verb used
 *			string dir -- the direction of movement
 */
public string
scenery_msgs(object ob, string vb, string dir)
{
    string desc;

    if (dir == "northeast" ||
	dir == "upstream")
    {
	desc =  BSN("As you travel upstream, "+
	            "the river bends more to the north.");
    }
    else if (dir == "southwest" ||
	     dir == "downstream")
    {
    	desc = BSN("As you travel downstream, the river curves in "+
	           "an ever-widening arc from southwest to southeast.");
    }
    else
    {
	desc = "";
    }
    return desc;
} /* scenery_msgs */
