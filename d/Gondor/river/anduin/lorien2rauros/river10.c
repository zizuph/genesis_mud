/*
 * /d/Gondor/river/anduin/lorien2rauros/river10.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * At the day 5 campsite, 200 miles south of the silverlode
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
	BSN("At the day 5 campsite, 200 miles downstream "+
	   "from the silverlode."));
    set_short("on the River Anduin");
    /* use tod_descs to append time-of-day descriptions to long
     * and to handle sky items
     */
    set_tod_long(
	"The Anduin bends from northwest to south, flowing "+
	"past bleak, lifeless shores.");

    set_tod_landname("the Brown Lands");
    set_tod_landtype("river");
    set_tod_prependshort(1);
    set_long(tod_descs);
    add_item( ({ "sky", "sun", "moon", "star", "stars" }), tod_descs );


    set_watertype("river");
    set_watername("River Anduin");
    set_waterrefs( ({ "great river", "waters", "water", "river", "anduin",
	"river anduin", "anduin river" }) );
    set_downstreamdir("south");
    set_upstreamdir("northwest");
    set_currentstr(5);	/* strong */
    set_depth(1524); /* 50 feet */
    /* no rocks */

    add_exit("river09", "northwest");
    set_distance("northwest", 20);
    add_exit("river11", "south");
    set_distance("south", 20);
    add_exit("riverbottom10", "down");
    add_exit("beach10w", "west");

    add_item( ({ "great river", "waters", "water", "river anduin",
	"anduin river", "anduin", "river" }),
	BSN("The water is deep and its motion swift and silent."));
    add_item( ({ "eastern bank", "east bank", "eastern shore",
	"east shore", }),
	BSN("Bleak hills rise sharply from the river to the east."));
    add_item( ({ "western bank", "west bank", "western shore",
	"west shore", }),
	BSN("From a narrow beach along the water's edge, "+
	    "the western shore climbs to bare, chalky hills."));
    add_item( ({ "shore", "shores", "river bank", "river banks",
   	 "bank", "banks" }),
	BSN("The shores, bare of tree or shrub, rise on either side "+
	    "to chalky hills. The eastern shore climbs steeply away "+
	    "from the water, but on the western shore "+
	    "a narrow beach lies at the water's edge."));
    add_item( ({ "brown lands", "land", "chalky hills", "bleak hills",
	"bare hills", "bare chalky hills", "hill", "hills" }), 
	BSN("The hills rise in rumpled folds on either side of "+
	    "the Anduin."));
    add_item( ({ "rumpled folds", "folds" }),
	BSN("The hills curve like rumpled folds of heavy cloth."));
    add_item( ({ "water's edge", "edge", "flat narrow strip",
	"narrow strip", "flat strip", "strip", "narrow beach",
	"flat beach", "beach" }),
	BSN("A flat, narrow strip of beach runs along the shore "+
	    "to the west."));
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

    if (dir == "northwest" ||
	dir == "upstream")
    {
	desc =  BSN("As you travel upstream, "+
	            "the river curves gently to the west.");
    }
    else if (dir == "south" ||
	     dir == "downstream")
    {
    	desc = BSN("As you travel downstream, the river bends to the "+
	           "southwest, and the hills decline into a gentle valley.");
    }
    else
    {
	desc = "";
    }
    return desc;
} /* scenery_msgs */
