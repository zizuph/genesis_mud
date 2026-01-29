/*
 * /d/Gondor/river/anduin/carrock2lorien/river03.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * 35 miles south of the Carrock, at the Old Forest Road
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
public int	swim_float_fatigue(int skill, string dir, int type,
				   object pl);
public string	scenery_msgs(object ob, string vb, string dir);


/*
 * Function name:	create_anduin_onwater
 * Description	:	set up the room
 */
public void
create_anduin_onwater()
{
    add_prop(OBJ_S_WIZINFO, "35 miles south of the Carrock, " +
	"at the Old Forest Road.\n");
    set_short("in the Old Ford");

    /* use tod_descs to append time-of-day descriptions to long
     * and to handle sky items
     */
    set_tod_long(
	"The Anduin widens, and from either shore a track leads " +
	"into water which is just shallow enough to cross afoot. " +
	"Beyond the ford, the waters deepen as they flow south.");
    set_tod_landname("the vale of Anduin");
    set_tod_landtype("ford");
    set_tod_prependshort(0);
    set_long(tod_descs);
    add_item( ({ "sky", "sun", "moon", "star", "stars" }), tod_descs );

    /* set up water stuff */
    set_watertype("river");
    set_watername("River Anduin");
    set_waterrefs( ({ "great river", "waters", "water", "river", "anduin",
	"river anduin", "anduin river", "old ford", "ford", }) );
    set_upstreamdir("north");
    set_downstreamdir("south");
    set_currentstr(3);	/* moderate */
    set_depth(MAX_WADE_DEPTH);
    /* no rocks */

    add_exit("river02", "north");
    set_distance("north", 20);
    add_exit("river04", "south");
    set_distance("south", 15);
    add_exit("riverbottom03", "down");
    add_exit("old_road_east", "east");
    add_exit("old_road_west", "west");

    add_item( ({ "great river", "waters", "water", "river anduin",
	"anduin river", "anduin", "river", "old ford", "ford", }),
	BSN("The Anduin is very wide here, and barely shallow " +
	    "enough to wade. Downstream, it grows deeper as " +
	    "it stretches endlessly south."));
    add_item( ({ "land", "view", "vale", "inland",
	"broad plain", "broad plains", "plain", "plains", }),
	BSN("Rolling grasslands stretch away to east and west."));
    add_item( ({ "river bank", "river banks", "bank", "banks", "shore",
	"shores", "either shore", }),
	BSN("From each shore, an overgrown track leads down into the " +
	    "ford. Broad plains of grass extend east and west beyond " +
	    "the tracks."));
    add_item( ({ "track", "tracks", }),
	BSN("The tracks leading into the ford are grassy and " +
	    "appear little used."));
    add_item( ({ "eastern bank", "east bank", "eastern shore",
	"east shore", "east track", "eastern track", }),
	BSN("A dusty track leads straight east across the grasslands " +
	    "towards a dark line of trees on the horizon."));
    add_item( ({ "west horizon", "western horizon",
	"western bank", "west bank", "western shore", "west shore", 
	"western track", "west track", }),
	BSN("To the west, a dusty track disappears into a great plain " +
	    "of grass."));
    add_item( ({ "eastern horizon", "east horizon", "horizon", }),
	BSN("Far to the east, the track disappears into the " +
	    "vast forest of Mirkwood."));
    add_item( ({ "dark line of trees", "dark line", "line", 
	"line of trees", "trees", "vast forest of mirkwood",
	"forest of mirkwood", "forest", "mirkwood" }),
	BSN("The forest of Mirkwood looms on the east horizon, " +
	    "dark and ominous."));
    add_item( ({ "rolling grasslands", "rolling grassland",
    	"grasslands", "grassland", }),
	BSN("Broad plains of waist-high grass roll towards the " +
	    "horizons."));
    add_item( ({ "green grass", "green grasses", "waist-high grass",
	"waist-high grasses", "grass", "grasses", }),
	BSN("The green grasses are flecked with the gold of " +
	    "ripening seedheads. They grow thick and waist-high " +
	    "on either shore."));
    add_item( ({ "ripening seedhead", "ripening seedheads", "seeds",
	"seed", "gold flecks", "flecks", "gold", "golden seedhead",
	"golden seedheads", "seedhead", "seedheads", }),
	BSN("The grasses are tipped with golden seedheads."));
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


/*
 * Function name:	scenery_msgs
 * Description	:	mask parent to warn re the dangers of attempting
 *			to swim or float down 600 miles of river
 * Arguments	:	object ob -- the object that moved
 *			string vb -- "wash", "swim", "wade", "dive", "row"
 *			string dir -- the direction of movement
 * Returns	:	string -- the msg
 *
 */
public string
scenery_msgs(object ob, string vb, string dir)
{
    if ((dir == "south" ||
	 dir == "downstream") &&
	interactive(ob))
    {
	return BSN("The Great River stretches before you. " +
	    "You feel some unease as you contemplate the " +
	    "apparently endless waters.");
    }
    return ::scenery_msgs(ob, vb, dir);
} /* scenery_msgs */
