/*
 * /d/Gondor/river/anduin/lorien2rauros/river08.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * at the intersection of the limlight and the anduin,
 * ~160 miles downstream of the silverlode
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
	BSN("at the intersection of the limlight and the anduin, "+
	    "perhaps 10 miles downstream of the day 4 campsite, "+
	    "155 miles downstream from the silverlode."));
    set_short("on the River Anduin");

    /* use tod_descs to append time-of-day descriptions to long
     * and to handle sky items
     */
    set_tod_long("The waters bend from northeast to south, and "
	+ "the Limlight flows from the west to join the Great River. "
	+ "On either shore, the land declines into the gentle valley "
	+ "of the North Undeep.");

    set_tod_landname("the North Undeep");
    set_tod_landtype("river");
    set_tod_prependshort(1);
    set_long(tod_descs);
    add_item( ({ "sky", "sun", "moon", "star", "stars" }), tod_descs );

    /* water stuff */
    set_watertype("river");
    set_watername("River Anduin");
    set_waterrefs( ({ "great river", "waters", "water", "river", "anduin",
	"river anduin", "anduin river" }) );
    set_upstreamdir("northeast");
    set_downstreamdir("south");
    set_currentstr(5);	/* strong */
    set_depth(1524); /* 50 feet */
    /* no rocks */

    add_exit("river07", "northeast");
    set_distance("northeast", 30);
    add_exit("river09", "south");
    set_distance("south", 20);
    add_exit("riverbottom08", "down");
    /* no shore rooms for now */

    /* msgs that talk about the currents, waters, etc  must make
     * sense for both swim and row ...
     */
    set_no_exit_msg("west",
	BSN("The waters of the Limlight propel you back into the Anduin."));

    add_item( ({ "great river", "waters", "water", "river anduin",
	"anduin river", "anduin", "river" }),
	BSN("The Anduin bends here, its deep water "
	  + "flowing in a gentle curve from northeast to south."));
    add_item( ({ "limlight river", "river limlight", "limlight" }),
	BSN("The dancing waters of the Limlight flow from the west "
	  + "to join the Anduin."));
    add_item( ({ "eastern shore", "eastern bank", "western shore", 
	"western bank", "east shore", "east bank", "west shore",
	"west bank", "shore", "shores", "river bank", "river banks",
	"bank", "banks", "valley", 
	"valleys", "north undeep", "undeep" }),
	BSN("The North Undeep stretches away "
	  + "from the river to the southwest and northeast."));
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

    if (dir == "south" ||
	dir == "downstream")
    {
	desc = BSN("As you travel downstream, the river bends to the "+
	           "east and hills rise on either shore.");
    }
    else
    {
	desc = "";
    }
    return desc;
} /* scenery_msgs */
