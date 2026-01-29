/*
 * /d/Gondor/river/anduin/carrock2lorien/river04.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * 50 miles south of the Carrock, 15 miles south of the
 * Old Forest Road
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
public int	block_swim_south();


/*
 * Function name:	create_anduin_onwater
 * Description	:	set up the room
 */
public void
create_anduin_onwater()
{
    add_prop(OBJ_S_WIZINFO, "50 miles south of the Carrock, " +
	"25 miles south of the Old Forest Road.\n");
    set_short("on the River Anduin");

    /* use tod_descs to append time-of-day descriptions to long
     * and to handle sky items
     */
    set_tod_long(
	"The Great River flows through the middle of a great " +
	"plain of rippling grasses.");
    set_tod_landname("the vale of Anduin");	/* XXX */
    set_tod_landtype("river");
    set_tod_prependshort(1);
    set_long(tod_descs);
    add_item( ({ "sky", "sun", "moon", "star", "stars" }), tod_descs );

    /* set up water stuff */
    set_watertype("river");
    set_watername("River Anduin");
    set_waterrefs( ({ "great river", "waters", "water", "river",
	"anduin", "river anduin", "anduin river" }) );
    set_upstreamdir("north");
    set_downstreamdir("south");
    set_currentstr(4);	/* brisk */
    set_depth(610); /* 20 feet */
    /* no rocks */

    add_exit("river03", "north");
    set_distance("north", 15);
    add_exit("river05", "south", block_swim_south);
    set_distance("south", 25);
    add_exit("riverbottom04", "down");
    add_exit("beach04e", "east");

    add_item( ({ "flow", "great river", "waters", "water", "river anduin",
	"anduin river", "anduin", "river" }),
	BSN("The Anduin is quite wide, and its dark waters " +
	    "move swiftly south."));
    add_item( ({ "land", "view", "vale", "inland", "river bank",
	"river banks", "bank", "banks", "shore", "shores",
	"great plain", "great plains", "plain", "plains", }),
	BSN("Grasslands stretch to either horizon, green and " +
	    "gold and sprinkled with wildflowers."));
    add_item( ({ "eastern bank", "east bank", "eastern shore",
	"east shore", }),
	BSN("Grasses and wildflowers grow thickly along the " +
	    "eastern shore."));
    add_item( ({ "west horizon", "western horizon", 
	"western bank", "west bank", "western shore", "west shore", }),
	BSN("A great plain of grass extends west as far as the " +
	    "eye can see."));
    add_item( ({ "eastern horizon", "east horizon", "horizon", }),
	BSN("Far to the east, a dark line of trees runs along " + 
	    "the horizon."));
    add_item( ({ "dark line of trees", "dark line", "line", 
	"line of trees", }),
	BSN("The dark line is the western edge of the forest " +
	    "of Mirkwood."));
    add_item( ({ "trees", "western edge", "edge", "forest",
	"forest of mirkwood", "mirkwood" }),
	BSN("From this distance, the forest is just a dark line " +
	    "on the horizon."));
    add_item( ({ "rippling grass", "rippling grasses",
	"green grass", "green grasses", "grass", "grasses", }),
	BSN("The grasses grow waist-high, and ripple in the " +
	    "slightest breeze."));
    add_item( ({ "flower", "wildflower", "flowers", "wildflowers",  }),
	BSN("Wildflowers grow among the grasses, sprinkling the " +
	    "plains with bright colours."));
    add_item( ({ "bright colour", "bright colours", "colour",
	"colours" }),
	BSN("The flowers seem to bloom in all colours. They " +
	    "make a cheerful show against the green grass."));
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
    if (dir == "east")
    {
	return 0;
    }
    return ::swim_float_fatigue(skill, dir, type, pl);
} /* swim_float_fatigue */


/*
 * Function name:	block_swim_south
 * Description	:	block attempts to swim south. we want them to 
 *			have to use boats.
 * Returns	:	0 if exit is allowed, 1 if not
 */
public int
block_swim_south()
{
    string	vb = QVB;
    if (vb == "south" ||
	vb == "swim")
    {
	WRITE("You swim south a bit, but the river seems endless. " +
	    "Discouraged, you abandon the attempt.");
	return 1;
    }
    return 0;
} /* block_swim_south */
