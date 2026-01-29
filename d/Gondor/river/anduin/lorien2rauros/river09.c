/*
 * /d/Gondor/river/anduin/lorien2rauros/river09.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * ~20 miles downstream of intersection with the limlight,
 * halfway between limlight and the day 5 campsite
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
	BSN("~20 miles downstream of intersection with the limlight, "+
	    "180 miles downstream from the silverlode, "+
	    "halfway between limlight and the day 5 campsite."));
    set_short("on the River Anduin");

    /* use tod_descs to append time-of-day descriptions to long
     * and to handle sky items
     */

    set_tod_long("The Great River flows from west to east "+
	"among bare, wind-scoured hills.");

    set_tod_landname("the Brown Lands");
    set_tod_landtype("river");
    set_tod_prependshort(1);
    set_long(tod_descs);
    add_item( ({ "sky", "sun", "moon", "star", "stars" }), tod_descs );

    /* water stuff */
    set_watertype("river");
    set_watername("River Anduin");
    set_waterrefs( ({ "great river", "waters", "water", "river", "anduin",
	"river anduin", "anduin river" }) );
    set_downstreamdir("east");
    set_upstreamdir("west");
    set_currentstr(5);	/* strong */
    set_depth(1524); /* 50 feet */
    /* no rocks */
    
    add_exit("river08", "west");
    set_distance("west", 20);
    add_exit("river10", "east");
    set_distance("east", 20);
    add_exit("riverbottom09", "down");
    /* no shore rooms for now */

    add_item( ({ "great river", "waters", "water", "river anduin",
	"anduin river", "anduin", "river" }),
	BSN("The waters of the Anduin are deep and swift."));
    add_item( ({ "eastern bank", "east bank", "eastern shore",
	"east shore", "western bank", "west bank", "western shore",
	"west shore", "shore", "shores", "river bank", "river banks",
	"bank", "banks" }),
	BSN("Bleak hills, swept bare by the wind, rise on either "+
	"shore."));
    add_item( ({ "brown lands", "land", "wind-scoured hills", "bleak hills",
	"hill", "hills" }), 
	BSN("The hills are bare, and appear empty of life."));

} /* create_anduin_onwater */


/*
 * Function name:	scenery_msgs
 * Description	:	mask parent to give a "the river bends" msg
 *			if people or boats are going upstream.
 * Arguments	:	object ob -- who/what is moving
 *			string vb -- the verb used
 *			string dir -- the direction of movement
 */
public string
scenery_msgs(object ob, string vb, string dir)
{
    string desc;

    if (dir == "west" ||
	dir == "upstream")
    {
	desc = BSN("As you travel upstream, the river bends to the "+
	           "north, and the hills gradually flatten into a "+
	           "shallow valley.");
    }
    else if (dir == "east" ||
	     dir == "downstream")
    {
	desc = BSN("As you travel downstream, the river gradually "+
	           "bends to the southeast.");
    }
    else
    {
	desc = "";
    }
    return desc;
} /* scenery_msgs */
