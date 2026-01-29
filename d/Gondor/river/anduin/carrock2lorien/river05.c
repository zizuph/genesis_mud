/*
 * /d/Gondor/river/anduin/carrock2lorien/river05.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * 75 miles south of the Carrock
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
public void	enter_inv(object ob, object from);
public void	wash_ashore(object pl);
public int	block_swim_south();


/*
 * Function name:	create_anduin_onwater
 * Description	:	set up the room
 */
public void
create_anduin_onwater()
{
    add_prop(OBJ_S_WIZINFO, "75 miles south of the Carrock.\n");
    set_short("on the River Anduin");

    /* use tod_descs to append time-of-day descriptions to long
     * and to handle sky items
     */
    set_tod_long(
	"The deep waters flow south, dark and swift, between " +
	"rolling grasslands.");
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
    set_currentstr(5);	/* strong */
    set_depth(1524); /* 50 feet */
    /* no rocks */

    add_exit("river04", "north"); 
    set_distance("north", 25); 
    add_exit("river06", "south", block_swim_south);
    set_distance("south", 25);
    add_exit("riverbottom05", "down");
    add_exit("beach05e", "east");

    add_item( ({ "flow", "great river", "waters", "water",
	"river anduin", "anduin river", "anduin", "river" }),
	BSN("The dark waters roll south between broad plains of " +
	    "grass sprinkled with wildflowers."));
    add_item( ({ "land", "view", "vale", "inland", "river bank",
	"river banks", "bank", "banks", "shore", "shores",
	"rolling grassland", "rolling grasslands",
	"undulating grassland", "undulating grasslands",
	"grassland", "grasslands", "broad plain", "broad plains",
	"plain", "plains", }),
	BSN("Broad plains stretch away from the " +
	    "river like a rumpled green blanket."));
    add_item( ({ "eastern bank", "east bank", "eastern shore",
	"east shore", }),
	BSN("The eastern shore is a blanket of waist-high grasses, " +
	    "dotted with flowers."));
    add_item( ({ "west horizon", "western horizon", "side",
	"western bank", "west bank", "western shore", "west shore", }),
	BSN("A broad plain of grass stretches west to the horizon."));
    add_item( ({ "eastern horizon", "east horizon", "horizon", }),
	BSN("Far beyond the grasslands to the east, Mirkwood darkens " +
	    "the horizon."));
    add_item( ({ "darkening", "forest", "forest of mirkwood",
	"mirkwood" }),
	BSN("From this distance, Mirkwood is just a darkening of " +
	    "the east horizon."));
    add_item( ({ "waist-high grass", "waist-high grasses",
	"grass", "grasses", }),
	BSN("The grasses, tall and thick, are sprinkled with " +
	    "wildflowers."));
    add_item( ({ "flower", "wildflower", "flowers", "wildflowers",  }),
	BSN("The wildflowers are bright dots of colour against " +
	    "the green grass."));
    add_item( ({ "bright dots of colour", "bright dots", "dots", 
	"colour", "colours" }),
	BSN("Although small, the wildflowers are brilliantly coloured."));
    add_item( ({ "folds", "rumpled green blanket", "rumpled blanket",
	"green blanket", "blanket", }),
	BSN("The undulating grasslands lie in folds on either " +
	    "side of the Anduin."));
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
 * Function name:	enter_inv
 * Description	:	mask parent to wash floating players ashore
 * Arguments	:	object ob -- the entering object
 *			object from -- its source
 */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (living(ob))
    {
	set_alarm(5.0, 0.0, &wash_ashore(ob));
    }
} /* enter_inv */


/*
 * Function name:	wash_ashore
 * Description	:	wash floating players ashore
 * Arguments	:	object pl -- the player
 */
public void
wash_ashore(object pl)
{
    object 	savetp;

    if (living(pl) &&
	ENV(pl) == TO)
    {
	savetp = TP;
	set_this_player(pl);
	write("The current swirls to the east and washes you ashore.\n");
	SAYBB(" washes ashore.");
	pl->move_living("M", (CARROCK_TO_LORIEN_DIR + "beach05e"));
	SAYBB(" arrives.");
	pl->remove_prop(OBJ_I_WATER_MOVE);
	set_this_player(savetp);
    }
} /* wash_ashore */


/*
 * Function name:	block_swim_south
 * Description	:	block attempts to swim south. we want them to have to
 *			use boats.
 * Returns	:	0 if exit is allowed, 1 if not
 */
public int
block_swim_south()
{
    string	vb = QVB;
    if (vb == "south" ||
	vb == "swim")
    {
	WRITE("You begin to swim south, but after a few moments in " +
	    "the deep chill river, you give up and head for shore.");
	TP->move_living("east", (CARROCK_TO_LORIEN_DIR + "beach05e"));
	return 1;
    }
    return 0;
} /* block_swim_south */


/*
 * Function name:	check_capsize
 * Description	:	mask parent to force capsize if no or unskilled pilot
 * Arguments	:	object ob -- the boat
 * Returns	:	1 if capsizes, 0 if not
 */
public int
check_capsize(object ob)
{
    object	pilot = ob->query_pilot();


    if (!objectp(pilot) ||
        pilot->query_skill(SS_BOAT_HANDL) < query_min_swim_skill(-1))
    {
	return 1;
    }
    return ::check_capsize(ob);
} /* check_capsize */
