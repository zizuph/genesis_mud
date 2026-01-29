/*
 * /d/Gondor/river/anduin/carrock2lorien/river02.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * 15 miles south of the Carrock, 20 miles north of
 * the Old Forest Road.
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
public int	swim_float_fatigue(int skill, string dir, int type, object pl);


/*
 * Function name:	create_anduin_onwater
 * Description	:	set up the room
 */
public void
create_anduin_onwater()
{
    add_prop(OBJ_S_WIZINFO, "15 miles south of the Carrock, "+
	"20 miles north of the Old Forest Road.\n");
    set_short("on the River Anduin");

    /* use tod_descs to append time-of-day descriptions to long
     * and to handle sky items
     */
    set_tod_long(
	"The waters roll swiftly south between wide "+
	"grasslands.");
    set_tod_landname("the vale of Anduin");	/* XXX */
    set_tod_landtype("river");
    set_tod_prependshort(1);
    set_long(tod_descs);
    add_item( ({ "sky", "sun", "moon", "star", "stars" }), tod_descs );

    /* set up water stuff */
    set_watertype("river");
    set_watername("River Anduin");
    set_waterrefs( ({ "great river", "waters", "water", "river", "anduin",
	"river anduin", "anduin river" }) );
    set_upstreamdir("north");
    set_downstreamdir("south");
    set_currentstr(3);	/* moderate */
    set_depth(610); /* 20 feet */
    /* no rocks */

    add_exit("river01", "north");
    set_distance("north", 15);
    add_exit("river03", "south");
    set_distance("south", 20);
    add_exit("riverbottom02", "down");
    add_exit("beach02e", "east");

    add_item( ({ "flow", "great river", "waters", "water", "river anduin",
	"anduin river", "anduin", "river" }),
	BSN("The Great River flows south without break or hindrance."));
    add_item( ({ "land", "view", "vale", "inland", "river bank",
	"river banks", "bank", "banks", "shore", "shores",
	"grassland", "grasslands", }),
	BSN("Great plains of grass stretch away from the river "+
	    "on either shore."));
    add_item( ({ "great plain", "great plains", "plain", "plains", }),
	BSN("The land beyond the river is smooth, and covered "+
	    "with waist-high grasses."));
    add_item( ({ "eastern bank", "east bank", "eastern shore",
	"east shore", }),
	BSN("A smooth carpet of grass stretches east to the horizon."));
    add_item( ({ "west horizon", "western horizon", 
	"western bank", "west bank", "western shore", "west shore", }),
	BSN("Waist-high grasses grow along the west shore, "+
	    "flowing uninterrupted as far as the eye can see."));
    add_item( ({ "eastern horizon", "east horizon", "horizon", }),
	BSN("A dark line of trees marches along the east horizon."));
    add_item( ({ "trees", "western edge", "edge", "forest",
	"forest of mirkwood", "mirkwood", "dark line of trees",
	"dark line", "line", "line of trees", }),
	BSN("The dark line of trees is all that can be seen of the "+
	    "forest of Mirkwood."));
    add_item( ({ "waist-high grass", "waist-high grasses",
	"smooth carpet", "smooth carpet of grass", "carpet",
	"carpet of grass", "grass", "grasses", }),
	BSN("The grasses grow tall and thick along the shores."));
} /* create_anduin_onwater */


/*
 * Function name:	swim_float_fatigue
 * Description	:	mask parent to always allow 'em to reach shore
 * Arguments	:	int skill -- player's swimming (or boating) skill
 *			string dir -- the direction to swim
 *			int type -- WATER_MOVE_SWIM, WATER_MOVE_FLOAT or 
 *				    WATER_MOVE_WADE
 *			object pl -- the player
 * Returns	:	positive integer -- the fatigue to be incurred;
 *			    caller must check against player's current fatigue
 *			    and decide whether to invoke add_fatigue(),
 *			    or to fail the swim attempt.
 *			or -1 -- cannot swim in that dir
 */
public int
swim_float_fatigue(int skill, string dir, int type, object pl)
{
    if (dir == "west" ||
	dir == "east")
    {
	return 0;
    }
    return ::swim_float_fatigue(skill, dir, type, pl);
} /* swim_float_fatigue */
