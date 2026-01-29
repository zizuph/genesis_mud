/*
 * /d/Gondor/river/anduin/lorien2rauros/river13w.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * at the day 6 campsite, brown lands to east, downs to west
 *
 * XXX would be nice if could configure land name for a dir
 * so west got "You swim west towards the shore." and east,
 * "You swim east towards the eyot.".
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
	BSN("at the day 6 campsite, about "+
	    "255 miles downstream from the silverlode."));
    set_short("on the River Anduin");

    /* use tod_descs to append time-of-day descriptions to long
     * and to handle sky items
     */
    set_tod_long("This narrow stretch of water flows south "+
	"between a small eyot and the rolling downs of the western "+
	"shore.");

    set_tod_landname("the Downs");
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
    set_currentstr( ({ 6, 6 }) ); /* rapid */ 
    set_depth(610); /* 20 feet */
    /* narrow, so harder to avoid shoals */
    set_rock_density(SCATTERED_ROCKS + 1);

    add_exit("river12", "north");
    set_distance("north", 2);
    add_exit("river14w", "south");
    set_distance("south", 20);
    add_exit("riverbottom13w", "down");
    add_exit("eyot", "east");
    /* only eyot shore rooms for now */


    add_item( ({ "narrow stretch", "channel", "great river", "waters",
	"water", "river anduin", "anduin river", "anduin", "river" }),
	BSN("The channel between the eyot and the shore is narrow, "+
	    "and there are gravel-shoals in the water."));
    add_item( ({  "shore", "shores", "river bank", "river banks",
	"bank", "banks", "western shore", "western bank",
	"west shore", "west bank", }),
	BSN("Chalky hills of withered grass rise to the west."));
    add_item( ({ "eastern shore", "eastern bank", "east shore",
	"east bank", "island", "small eyot", "eyot" }),
	BSN("Dense bushes cover the eyot, which barely rises above "+
	    "the level of the river."));
    add_item( ({ "dense bush", "dense bushes", "bush", "bushes", }),
	BSN("The bushes grow thickly over the eyot."));
    add_item( ({ "gravel", "shoals", "gravel-shoals" }),
	BSN("Long, narrow shoals of gravel lie just below the water."));
    add_item( ({ "horizon", "chalky hill", "chalky hills", "hill", "hills",
	"land", "down", "downs", }),
	BSN("High, sere downs extend west to the horizon."));
    add_item( ({ "turf", "grass" }),
	BSN("The grass appears withered and dry."));
} /* create_anduin_onwater */
