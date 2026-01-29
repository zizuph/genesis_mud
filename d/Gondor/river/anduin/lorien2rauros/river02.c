/*
 * /d/Gondor/river/anduin/lorien2rauros/river02.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * 20 miles south of the intersection with the Silverlode,
 * near the campsite for day 1.
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
public void		create_anduin_onwater();


/*
 * Function name:	create_anduin_onwater
 * Description	:	set up the room
 */
public void
create_anduin_onwater()
{
    add_prop(OBJ_S_WIZINFO,
	BSN("20 miles downstream from the intersection with the "+
	    "Silverlode, near the campsite for day 1."));
    set_short("on the River Anduin");

    /* use tod_descs to append time-of-day descriptions to long
     * and to handle sky items
     */
    set_tod_long(
	"Great trees line the banks of the Anduin, "
      + "and its deep dark waters roll southeast.");
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

    add_exit("river01", "northwest");
    set_distance("northwest", 20);
    add_exit("river03", "southeast");
    set_distance("southeast", 20);
    add_exit("riverbottom02", "down");
    /* no shore rooms for now */

    add_item( ({ "great river", "waters", "water", "river anduin",
	"anduin river", "anduin", "river" }),
	"The deep, swift-moving waters flow silently southeast.\n");
    add_item( ({ "eastern bank", "east bank", "western bank",
	"west bank", "wooded bank", "wooded banks", "river bank",
	"river banks", "bank", "banks", "eastern shore", "east shore",
	"western shore", "west shore", "wooded shore",
	"wooded shores", "shore", "shores" }),
	"Dense woods line both shores.\n");
    add_item( ({ "hill-lands", "tree", "trees", "forests",
	"forest", "woods" }),
	BSN("Trees stalk the edge of the river, "+
	    "blocking all views to east and west.") );
    
} /* create_anduin_onwater */
