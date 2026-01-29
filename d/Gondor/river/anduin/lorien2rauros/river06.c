/*
 * /d/Gondor/river/anduin/lorien2rauros/river06.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * 105 miles south of silverlode, at the campsite for day 3.
 *
 */

#pragma strict_types

inherit "/d/Gondor/river/anduin/anduin_onwater";

#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/std/water/onwater.h"
#include "../anduin.h"
inherit "/d/Gondor/common/lib/tod_descs";


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
	BSN("105 miles downstream from silverlode, "+
	    "at the campsite for day 3."));
    set_short("on the River Anduin");

    /* use tod_descs to append time-of-day descriptions to long
     * and to handle sky items
     */
    set_tod_long(
	"The deep waters flow southeast between open, treeless "
      + "shores.");
    set_tod_landtype("river");
    set_tod_landname("the Brown Lands");
    set_tod_prependshort(1);
    set_long(tod_descs);
    add_item( ({ "sky", "sun", "moon", "star", "stars" }), tod_descs );

    /* water stuff */
    set_watertype("river");
    set_watername("River Anduin");
    set_waterrefs( ({ "great river", "waters", "water", "river", "anduin",
	"river anduin", "anduin river" }) );
    set_downstreamdir("southeast");
    set_upstreamdir("northwest");
    set_currentstr(5);	/* strong */
    set_depth(1524); /* 50 feet */
    /* no rocks */

    add_exit("river05", "northwest");
    set_distance("northwest", 25);
    add_exit("river07", "southeast");
    set_distance("southeast", 25);
    add_exit("riverbottom06", "down");
    add_exit("beach06w", "west");

    add_item( ({ "great river", "waters", "water", "river anduin",
	"anduin river", "anduin", "river" }),
	"The waters of the Anduin are deep.\n");
    add_item( ({ "long formless slopes", "formless slopes", "slopes",
	"slope", "eastern bank", "east bank",
	"eastern shore", "east shore" }),
	BSN("On the eastern shore, long formless slopes stretch up "+
	    "and away."));
    add_item( ({ "plains", "grass", "western bank", "west bank",
	"western shore", "west shore" }),
	BSN("To the west, the land is flat and in many places "+
            "green with wide plains of grass. A narrow gravel beach "+
	    "runs along the water's edge."));
    add_item( ({ "brown lands", "banks", "river bank", "river banks",
	"bank", "land", "shore", "shores" }),
	BSN("The shores are bare. On the eastern shore, the land "+
	    "slopes up from the river; the western shore is flat, "+
	    "with a narrow beach."));
    add_item( ({ "narrow gravel beach", "gravel beach", "narrow beach",
	"water's edge", "western edge", "beach", "gravel" }),
	BSN("A narrow gravel beach runs along the western edge "+
	    "of the river."));
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

    if (dir == "southeast" ||
	dir == "downstream")
    {
	desc = BSN("As you travel downstream, "+
	           "the Anduin bends towards the south.");
    }
    else if (dir == "northwest" ||
	     dir == "upstream")
    {
    	desc = BSN("As you travel upstream, trees begin to "+
	           "cloak the shores.");
    }
    else
    {
	desc = "";
    }
    return desc;
} /* scenery_msgs */
