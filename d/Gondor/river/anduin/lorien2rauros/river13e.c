/*
 * /d/Gondor/river/anduin/lorien2rauros/river13e.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * at the day 6 campsite, brown lands to east, downs to west
 *
 *
 * XXX would be nice if could configure land name for a dir
 * so east got "You swim east towards the shore." and west,
 * "You swim west towards the eyot.".
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


/*
 * Function name:	create_anduin_onwater
 * Description	:	set up the room
 */
public void
create_anduin_onwater()
{
    add_prop(OBJ_S_WIZINFO,
	BSN("at the day 6 campsite, "+
	    "255 miles downstream from the silverlode."));
    set_short("on the River Anduin");

    /* use tod_descs to append time-of-day descriptions to long
     * and to handle sky items
     */
    set_tod_long(
	"The Great River broadens and grows more shallow as it flows "+
	"from northwest to south. Long stony beaches lie to the east, "+
	"and there is a small eyot near the western shore.");

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
    set_downstreamdir("south");
    set_upstreamdir("northwest");
    set_currentstr( ({ 6, 6 }) ); /* rapid */ 
    set_depth(610); /* 20 feet */
    set_rock_density(SCATTERED_ROCKS);

    add_exit("river12", "northwest");
    set_distance("northwest", 2);
    add_exit("river14e", "south");
    set_distance("south", 20);
    add_exit("riverbottom13e", "down");
    add_exit("eyot", "west");
    add_exit("beach13e", "east");

    add_item( ({ "great river", "waters", "water", "river anduin",
	"anduin river", "anduin", "river" }),
	BSN("The wide river glitters over occasional gravel-shoals."));
    add_item( ({  "shore", "shores", "river bank", "river banks",
	"bank", "banks" }),
	BSN("To the east are long beaches, and to the west a small eyot."));
    add_item( ({ "eastern shore", "eastern bank", "east shore",
	"east bank" }),
	BSN("Beyond the beaches on the east shore rise bleak, cheerless "+
	    "wolds."));
    add_item( ({ "western shore", "western bank", "west shore",
	"west bank", }),
	BSN("A low eyot lies near the west shore."));
    add_item( ({ "island", "small eyot", "eyot" }),
	BSN("The eyot lies not much above the level of the river."));
    add_item( ({ "river's surface", "water's surface", "surface",
	"gravel", "shoals", "gravel-shoals" }),
	BSN("Long shoals of gravel lie just below the water's surface."));
    add_item( ({ "rock", "rocks" }),
	BSN("Here and there, a rock juts up from the shoals."));
    add_item( ({ "beach", "long beach", "stony beach", "long beaches",
	"stony beaches", "beaches" }),
	BSN("The beaches along the eastern shore are long and narrow, "+
	    "and appear formed more from stone than from sand. "+
	    "Beyond them rises a bleak, treeless land."));
    add_item( ({ "plain", "plains", "land", "down", "downs",
	"wold", "wolds", }),
	BSN("The land rises into a high treeless plain, over which flows "+
	"a chill air from the East."));
} /* create_anduin_onwater */
