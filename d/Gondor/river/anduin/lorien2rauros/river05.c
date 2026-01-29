/*
 * /d/Gondor/river/anduin/lorien2rauros/river05.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * ~80 miles south of the silverlode, halfway between
 * the campsites for day 2 and day 3.
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
	BSN("~80 miles downstream from the silverlode, halfway between "+
	    "the campsites for day 2 and day 3."));
    set_short("on the River Anduin");

    /* use tod_descs to append time-of-day descriptions to long
     * and to handle sky items
     */
    set_tod_long(
	"The Great River flows southeast past lightly wooded shores.");
    set_tod_landname("the Hill-lands");
    set_tod_landtype("river");
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

    add_exit("river04", "northwest");
    set_distance("northwest", 20);
    add_exit("river06", "southeast");
    set_distance("southeast", 25);
    add_exit("riverbottom05", "down");
    /* no shore rooms for now */

    add_item( ({ "great river", "waters", "water", "river anduin",
	"anduin river", "anduin", "river" }),
	"The Anduin rolls southeast, swift and silent.\n");
    add_item( ({ "eastern bank", "east bank", "western bank",
	"west bank", "wooded bank", "wooded banks", "river bank", "river banks",
	"bank", "banks",
	"eastern shore", "east shore", "western shore",
	"west shore", "wooded shore", "wooded shores", "shore", "shores" }),
	"Light forest cloaks either shore.\n");
    add_item( ({ "tree", "trees", "light forest", "forests", "forest",
	"woods" }),
	BSN("The forests are somewhat thin, permitting glimpses of "+
	"the hills beyond."));
    add_item( ({ "hill-lands", "low domed hill", "low domed hills",
	"low hill", "low hills", "domed hill", "domed hills",
	"hill", "hills" }),
	BSN("In the distance, low domed hills curve gently upwards."));

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
	       "the trees thin and then fail altogether.");
    }
    else
    {
	desc = "";
    }
    return desc;
} /* scenery_msgs */
