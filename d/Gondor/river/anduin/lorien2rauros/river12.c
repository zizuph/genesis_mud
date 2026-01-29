/*
 * /d/Gondor/river/anduin/lorien2rauros/river12.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * just upstream of the day 6 campsite
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
	BSN("just upstream of the day 6 campsite, about "+
	    "253 miles downstream from the silverlode."));
    set_short("on the River Anduin");
    set_tod_long("The waters from the northwest split here to flow "+
	"south and southeast around a small eyot.");

    /* use tod_descs to append time-of-day descriptions to long
     * and to handle sky items
     */
    set_tod_landname("the Downs");
    set_tod_landtype("river");
    set_tod_prependshort(1);
    set_long(tod_descs);
    add_item( ({ "sky", "sun", "moon", "star", "stars" }), tod_descs );

    /* water stuff */
    set_watertype("river");
    set_watername("River Anduin");
    set_waterrefs( ({ "great river", "waters", "water", "river", "anduin",
	"river anduin", "anduin river" }) );
    set_downstreamdir( ({ "southeast", "south" }) );
    set_upstreamdir("northwest");
    set_currentstr( ({ 5, 4 }) );	/* strong, brisk */
    set_depth(1524); /* 50 feet */
    set_rock_density(SCATTERED_ROCKS);

    add_exit("river11", "northwest");
    set_distance("northwest", 33);
    add_exit("river13w", "south");
    set_distance("south", 2);
    add_exit("river13e", "southeast");
    set_distance("southeast", 2);
    add_exit("riverbottom12", "down");
    /* no shore rooms for now */

    add_item( ({ "great river", "waters", "water", "river anduin",
	"anduin river", "anduin", "river" }),
	BSN("The main waters of the river flow southeast, "+
	    "while a narrow channel cuts south between the "+
	    "eyot and the western shore."));
    add_item( ({ "main water", "main waters", }),
	BSN("The waters roll swiftly southeast, skirting a small "+
	    "eyot near the western short."));
    add_item( ({ "narrow channel", "channel", }),
	BSN("Narrow, roiled waters flow between the eyot and the "+
	    "western shore."));
    add_item( ({ "eastern shore", "eastern bank", "western shore",
	"western bank", "east shore", "east bank", "west shore",
	"west bank", "shore", "shores", "river bank", "river banks",
	"bank", "banks" }),
	BSN("Rolling, treeless downs rise on either side of the river."));
    add_item( ({ "downs" }),
	BSN("The long, treeless, short-turfed slopes appear dry."));
    add_item( ({ "grass", "turf" }),
	BSN("The grass is withered and short."));
    add_item( ({ "island", "small eyot", "eyot" }),
	BSN("The eyot is fairly small, and cloaked by low, tangled "+
	    "bushes."));
    add_item( ({ "bush", "bushes" }),
	BSN("Intertwined bushes, growing close to the ground, cover "+
	    "the eyot."));
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
	desc = BSN("As you travel upstream, the river curves in "+
	           "a gradually narrowing arc from northwest "+
		   "to northeast.");
    }
    else
    {
	desc = "";
    }
    return desc;
} /* scenery_msgs */
