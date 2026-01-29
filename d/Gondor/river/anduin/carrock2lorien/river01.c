/*
 * /d/Gondor/river/anduin/carrock2lorien/river01.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * at the Carrock, 35 miles north of the Old Forest Road.
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
    add_prop(OBJ_S_WIZINFO,
	"at the Carrock, 35 miles north of the Old Forest Road\n");
    set_short("on the River Anduin");

    /* use tod_descs to append time-of-day descriptions to long
     * and to handle sky items
     */
    set_tod_long(
	"The waters flow from northwest and northeast around a "+
	"great rock, then merge and roll swiftly south.");
    set_tod_landname("the vale of Anduin");
    set_tod_landtype("river");
    set_tod_prependshort(1);
    set_long(tod_descs);
    add_item( ({ "sky", "sun", "moon", "star", "stars" }), tod_descs );

    /* set up water stuff */
    set_watertype("river");
    set_watername("River Anduin");
    set_waterrefs( ({ "great river", "waters", "water", "river", "anduin",
	"river anduin", "anduin river" }) );
    set_upstreamdir( ({ "northwest", "northeast" }) );
    set_downstreamdir("south");
    set_currentstr(3);	/* moderate */
    set_depth(610); /* 20 feet */
    /* no rocks */

    add_exit("river00", "northeast");
    add_exit("river02", "south");
    set_distance("south", 15);
    add_exit("riverbottom01", "down");
    add_exit("fishcamp_s", "east");

    set_no_exit_msg("northwest",
	BSN("The current is too strong for you to travel northwest."));
    set_no_exit_msg("north",
	BSN("The Carrock is too steep for you to leave "+
	    "the river to the north."));

    add_item( ({ "flow", "great river", "waters", "water", "river anduin",
	"anduin river", "anduin", "river" }),
	BSN("Upstream, the Anduin flows around a great rock. "+
	    "To the northwest, it is narrow and "+
	    "very swift, but the northeast branch is wide and shallow. "+
	    "Below the rock, the waters join to flow south across "+
	    "the grasslands."));
    add_item( ({ "northwest channel", "northwest river", "northwest",
	"northwest branch", }),
	BSN("The waters to the northwest are deep, narrow and swift."));
    add_item( ({ "northeast channel", "northeast river", "northeast",
	"northeast branch", }),
	BSN("To the northeast, the Anduin is wide and shallow."));
    add_item( ({ "land", "view", "vale", "inland", "river bank",
	"river banks", "bank", "banks", "shore", "shores",
	"wide grassland", "wide grasslands", "grassland", "grasslands", }),
	BSN("Wide grasslands lie in gentle folds like a soft "+
	    "green blanket on either side of the river."));
    add_item( ({ "soft green blanket", "soft blanket", "green blanket",
	"blanket", }),
	BSN("The grasses stretch in smooth folds to the horizon."));
    add_item( ({ "undulation", "undulations", "smooth fold",
	"smooth folds", "gentle fold", "gentle folds", "fold", "folds", }),
	BSN("The undulations are so gentle that the land appears "+
	    "flat at first glance."));
    add_item( ({ "eastern bank", "east bank", "eastern shore",
	"east shore", }),
	BSN("The grassses flow like a green sea east, towards a "+
	    "dark line of trees on the horizon."));
    add_item( ({ "west horizon", "western horizon", 
	"western bank", "west bank", "western shore", "west shore", }),
	BSN("Tall grasses grow thickly on the west shore."));
    add_item( ({ "eastern horizon", "east horizon", "horizon", }),
	BSN("The edge of Mirkwood is just visible on the "+
	    "east horizon."));
    add_item( ({ "trees", "edge", "forest",
	"forest of mirkwood", "mirkwood", "dark line of trees",
	"dark line", "line", "line of trees", }),
	BSN("What little is visible of Mirkwood seems dark and ominous."));
    add_item( ({ "tall grass", "tall grasses",
	"green sea", "sea", "grass", "grasses", }),
	BSN("The grasses are tall and thick, and speckled with golden "+
	    "seedheads."));
    add_item( ({ "golden seedhead", "golden seedheads", "seedhead",
	"seedheads", }),
	BSN("The seedheads tip the grasses with gold."));

    add_item( ({ "great rock", "rock", "carrock", }),
	BSN("Cropping out of the ground, right in the path of the "+
	    "Anduin, is a great rock, almost a hill of stone, like "+
	    "a huge piece cast miles into the plain by some giant."));
    add_item( ({ "huge piece", "piece", "great hill", "great hill of stone",
	"hill of stone", "hill", }),
	BSN("The great hill is steep, but seems to be flat on top."));
    add_item( ({ "hilltop", "hill top", "top", }),
	BSN("The top of the hill of stone seems quite flat."));
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
