/*
 * /d/Gondor/river/anduin/carrock2lorien/river00.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * in the Carrock ford, 35 miles north of the Old Forest Road.
 */

#pragma strict_types

inherit "/d/Gondor/river/anduin/anduin_onwater";
inherit "/d/Gondor/common/lib/tod_descs";

#include <composite.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/std/water/onwater.h"
#include "../anduin.h"

#define	STONES	(CARROCK_TO_LORIEN_DIR+"carrock_stones")


/* prototypes */
public void	create_anduin_onwater();
public void	init();
public string	exa_stones();
public int	do_climb(string arg);
public int	swim_float_fatigue(int skill, string dir, int type, object pl);

static object	Stones;		/* the stones room */


/*
 * Function name:	create_anduin_onwater
 * Description	:	set up the room
 */
public void
create_anduin_onwater()
{
    add_prop(OBJ_S_WIZINFO,
	"in the Carrock ford, 35 miles north of the Old Forest Road\n");
    set_short("in the Carrock ford");

    /* use tod_descs to append time-of-day descriptions to long
     * and to handle sky items
     */
    set_tod_long(
	"The Anduin is broad and shallow here, and a line of "+
	"huge flat stones leads across the river from the Carrock "+
	"to the east shore. Below the ford, the river "+
	"deepens as it flows southwest through the grasslands.");
    set_tod_landname("the vale of Anduin");
    set_tod_landtype("river");
    set_tod_prependshort(1);
    set_long(tod_descs);
    add_item( ({ "sky", "sun", "moon", "star", "stars" }), tod_descs );

    /* set up water stuff */
    set_watertype("river");
    set_watername("River Anduin");
    set_waterrefs( ({ "ford", "great river", "waters", "water",
	"river", "anduin", "river anduin", "anduin river" }) );
    set_upstreamdir("north");
    set_downstreamdir("southwest");
    set_currentstr(1);	/* slight */
    set_depth(MIN_SWIM_DEPTH - 10);	/* shallow */
    set_rock_density(SCATTERED_ROCKS);

    add_exit("river01", "southwest");
    add_exit("carrock_beach", "west");
    add_exit("fishcamp_n", "east");

    set_no_exit_msg("north",
	BSN("The river is too rocky, and the current too strong, "+
	    "for you to travel north."));

    add_item( ({ "great river", "waters", "water", "river anduin",
	"anduin river", "anduin", "river" }),
	BSN("The shallow waters gurgle as they flow past the stones of "+
	    "the ford. To the southwest, the river grows narrower and "+
	    "more deep."));
    add_item( ({ "carrock ford", "ford", "line", "huge flat rock",
	"huge rock", "flat rock", "rock", "huge flat rocks",
	"huge rocks", "flat rocks", "rocks", "huge flat stone",
	"huge stone", "flat stone", "stone", "huge flat stones",
	"huge stones", "flat stones", "stones", }),
	exa_stones);
    add_item( ({ "land", "view", "vale", "inland", "river bank",
	"river banks", "bank", "banks", "shore", "shores",
	"east grasslands", "eastern grassland", 
	"wide grassland", "wide grasslands", "grassland", "grasslands", }),
	BSN("Tall grasses, green flecked with gold, stretch "+
	    "east from the river."));
    add_item( ({ "near side", "eastern horizon", "east horizon", "horizon",
    	"eastern bank", "east bank", "eastern shore", "east shore", }),
	BSN("The eastern shore is carpeted with thick green grasses."));
    add_item( ({ "far side", "west horizon", "western horizon", 
	"western bank", "west bank", "western shore", "west shore", }),
	BSN("A great hill of stone rises out of the river to the west. "+
	    "Beyond the hill, on the far side of the Anduin, still "+
	    "more grasses stretch away west."));
    add_item( ({ "tall grass", "tall grasses",
	"thick grass", "thick grasses", "thick green grass",
	"thick green grasses", "green grass", "green grasses",
	"grass", "grasses", }),
	BSN("The grasses grow waist-high, thick and sparsely flecked "+
	    "with gold."));
    add_item( ({ "tips", "flecks", "gold", }),
	BSN("Flecks of gold sparkle on the very tips of the grass."));

    add_item( ({ "great rock", "rock", "great hill", "great hill of stone",
	"hill of stone", "hill", "carrock", }),
	BSN("The Carrock juts out of the river like a last outpost of "+
	    "the distant mountains. A path climbs from the water, up "+
	    "and around the hill."));
    add_item( ({ "solid rock", "rock", "last outpost", "outpost", }),
	BSN("The hill appears to be solid rock, gray and massive."));
    add_item( ({ "well worn path", "path", }),
	BSN("A well worn path leads west from the water, winding "+
	    "around to the top of the hill."));
    add_item( ({ "hilltop", "hill top", "top", }),
	BSN("The hill is quite flat on top."));
    add_item( ({ "distant mountain", "distant mountains",
     	"mountain", "mountains", }),
	BSN("The Misty Mountains lie far to the west. They are "+
	    "not visible from here."));
} /* create_anduin_onwater */


/*
 * Function name:	init
 * Description	:	add 'climb'
 */
public void
init()
{
    ::init();
    add_action(do_climb, "climb");
} /* init */


/*
 * Function name:	exa_stones
 * Description	:	VBFC for the stones -- mention anyone standing there
 * Returns	:	the stones desc
 */
public string
exa_stones()
{
    object	*live_on_stones;
    string	desc;
    int		s;

    desc = BSN("A ford of flat stones, each easily three feet wide, "+
	    "crosses the river from the Carrock to the eastern "+
	    "grasslands.");

    if (!objectp(Stones))
    {
	STONES->short();
	Stones = find_object(STONES);
    }
    live_on_stones = FILTER_LIVE(all_inventory(Stones));
    if (!TP->query_wiz_level())
    {
	/* assume that from this distance, cannot see hidden or invis */
	live_on_stones = filter(filter(live_on_stones,
	    &not() @ &->query_prop(OBJ_I_HIDE)),
	    &not() @ &->query_invis());
    }
    switch (sizeof(live_on_stones))
    {
    case 0:
	break;
    case 1:
	desc += BSN(live_on_stones[0]->query_Art_name(TP)+
		" is standing on a stone in the ford.");
	break;
    default:
	desc += BSN(CAP(COMPOSITE_LIVE(live_on_stones))+
		" are standing on stones in the ford.");
    }
    return desc;
} /* exa_stones */


/*
 * Function name:	do_climb
 * Description	:	handle attempts to climb on stones
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 */
public int
do_climb(string arg)
{
    object	tp = TP;

    if (strlen(arg) &&
	parse_command(LOW(arg), ({}), "[up] [on] / [onto] [the] "+
	    "[huge] [flat] 'stone' / 'stones' / 'rock' / 'rocks'"))
    {
	WRITE("You climb up onto a stone in the ford.");
	tp->move_living("onto the stones", STONES);
	return 1;
    }
    NF0("Climb what?\n");
} /* do_climb */


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
