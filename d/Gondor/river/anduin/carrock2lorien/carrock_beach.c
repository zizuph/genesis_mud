/*
 * /d/Gondor/river/anduin/lorien2rauros/carrock_beach.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * beach on carrock
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/water/shore_room";
inherit "/d/Gondor/common/lib/tod_descs";
inherit "/d/Gondor/common/lib/drink_water";
inherit "/d/Gondor/common/lib/dig";

#include <composite.h>		/* for COMPOSITE_WORDS */
#include <filter_funs.h>	/* for FILTER_LIVE */
#include <language.h>		/* for LANG_ADDART */
#include <macros.h>		/* for QCTNAME */
#include <stdproperties.h>	/* for OBJ_I_* */
#include "/d/Gondor/defs.h"	/* always */
#include "../anduin.h"

#define	CAVE	(CARROCK_TO_LORIEN_DIR+"carrock_cave")
#define	RIVER	(CARROCK_TO_LORIEN_DIR+"river00")
#define	STONES	(CARROCK_TO_LORIEN_DIR+"carrock_stones")

/* prototypes */
public void	create_shore_room();
public void	reset_room();
public void	init();
public void	leave_inv(object ob, object dest);
public void	move_msg();
public int	unq_move(string str);
public string	exa_stones();
public int	do_enter(string arg);
public void	dig_results(object digger);

static object	Stones;		/* the stones room */
static int	Stuffhere;	/* anything in the sand? */


/*
 * Function name:	create_shore_room
 * Description	:	set up the beach
 */
public void
create_shore_room()
{
    FIX_EUID;		/* might clone objects in dig_results() */

    set_short("beach");

    /* use tod_descs to append time-of-day descriptions to long
     * and to handle sky items
     */
    set_tod_long(
	"A wide, sandy beach slopes gently to the ford, where "+
	"a line of wide flat stones leads east across the Anduin. "+
	"To the west, a narrow path climbs the wall of the Carrock.");
    set_tod_landname("the vale of Anduin");
    set_tod_landtype("beach");
    set_long(tod_descs);
    add_item( ({ "sky", "sun", "moon", "star", "stars" }), tod_descs );

    add_exit("river00", "east", 0, 2, 1);
    add_exit("carrock_path1", "west", move_msg, 7);
    add_exit("carrock_path1", "up", move_msg, 7, 1);

    set_no_exit_msg( ({ "northwest", "southwest", }),
	BSN("The rock wall is far too steep to climb."));
    set_no_exit_msg( ({ "northeast", "north", "southeast", "south", }),
	BSN("You wander along the beach for a bit."));

    set_water("east",
	({ "ford", "great river", "waters", "water", "river", "anduin",
	"river anduin", "anduin river" }) );

    set_drink_from( ({ "ford", "great river", "river anduin", "anduin river",
	"anduin", "river", }) );

    add_item( ({ "great river", "waters", "water", "river", "anduin",
	"river anduin", "anduin river" }),
	&exa_water(RIVER, 
	    "The Anduin is wide and shallow here, and it splashes "+
	    "cheerfully past the stones of the ford.\n"));

    add_item( ({ "wide sandy beach", "wide beach", "sandy beach",
	"beach", }),
	BSN("The sandy beach is wide and quite flat. To the north, "+
	    "it narrows and bends around the rock wall."));
    add_item( ({ "coarse sand", "sand", "ground", "dirt" }),
	BSN("Coarse brown shifts softly underfoot."));

    add_item( ({ "route", "line of stones", "line", "wide flat stone", 
	"wide flat stones", "wide stone", "wide stones", "flat stone",
	"flat stones", "stone", "stones", }),
	exa_stones);
    add_item( ({ "ford", "carrock ford", }),
	BSN("Flat stones have been planted in the river to "+
	    "allow passage from the Carrock to the east shore."));
    add_item( ({ "land", "view", "vale", "inland", "river bank",
	"river banks", "bank", "banks", "shore", "shores",
	"east grasslands", "eastern grassland", 
	"wide grassland", "wide grasslands", "grassland", "grasslands", }),
	BSN("Tall green grasses flow away from the river on "+
	    "the east shore."));
    add_item( ({ "eastern horizon",
	"east horizon", "horizon", "eastern bank", "east bank",
	"eastern shore", "east shore", }),
	BSN("Tall grasses, waving gently in the breeze, cloak the "+
	    "east shore."));
    add_item( ({ "western bank", "west bank", "western shore",
	"west shore", }),
	BSN("The Carrock rises sharply to the west, blocking all view "+
	    "of the western shore."));
    add_item( ({ "tall grass", "tall grasses",
	"thick grass", "thick grasses", "thick green grass",
	"thick green grasses", "green grass", "green grasses",
	"grass", "grasses", }),
	BSN("The grasses are easily waist-high, and very thick."));
    add_item( ({ "rock wall", "east wall", "wall", "carrock", }),
	BSN("The east wall of the Carrock rises nearly vertically "+
	    "from the beach. At the base of the wall, there opens "+
	    "a narrow fissure."));
    add_item( ({ "base", "narrow fissure", "fissure", }),
	BSN("At first glance, the fissure appears quite narrow. "+
	    "However, on closer examination, that is just "+
	    "a trick of the light -- it is really a good-sized "+
	    "opening in the rock wall."));
    add_item( ({ "large cave", "cave", "good-sized opening", "opening", }),
	BSN("It is difficult to see inside the opening from here."));
    add_item( ({ "side", "well worn path", "narrow path", "path", }),
	BSN("A well worn path, with many steps to it, climbs "+
	    "the Carrock to the west."));
    add_item( ({ "step", "steps", }),
	BSN("The steps are widely spaced, as if made by someone quite tall."));
    add_item( ({ "hilltop", "hill top", "top", }),
	BSN("From this vantage point, it is difficult to see the "+
	    "top of the Carrock."));


    add_cmd_item( ({ "up rock wall", "up east wall", "up wall", "up carrock",
    	"rock wall", "east wall", "wall", "carrock", }),
	"climb",
	BSN("You have not the skill to climb the steep wall "+
	    "of the Carrock. You would do better to use the path."));

    set_dig_pattern("[in] [the] [coarse] [brown] 'sand' / 'here'");
    set_dig_message("in the sand");

    reset_room();
} /* create_shore_room */


/*
 * Function name:	reset_room
 * Description	:	reset flag for stuff in sand
 */
public void
reset_room()
{
    ::reset_room();
    Stuffhere = 1;
} /* reset_room */


/*
 * Function name:	init
 * Description	:	add drink verb, "enter"
 */
public void
init()
{
    ::init();
    init_drink();
    add_action(dig_here,	"dig");
    add_action(do_enter,	"enter");
} /* init */


/*
 * Function name:	leave_inv
 * Description	:	be sure digging alarm is cleared if digger
 *			manages to leave in spite of paralyze
 * Arguments	:	object ob -- the departing object
 *			object dest -- its destination
 */
public void
leave_inv(object ob, object dest)
{
    stop_digging(ob);
    ::leave_inv(ob, dest);
} /* leave_inv */


/*
 * Function name:	move_msg
 * Description	:	do nice msg re climbing the path
 * Returns	:	0 -- exit always succeeds
 */
public int
move_msg()
{
    write( ({
	"You struggle to take the tall steps in stride.\n",
	"You climb the path, stretching a bit to manage the tall steps.\n",
	"You clamber up the tall steps.\n",
	"With some difficulty, you climb the widely-spaced steps.\n",
	})[random(4)] );
    return 0;
} /* move_msg */


/*
 * Function name:	unq_move
 * Description	:	mask parent's unq_move() so that "east" moves us
 *			onto the stones, but "swim" into the river.
 * Arguments	:	string str - the command line argument.
 * Returns	:	1 on success, 0 o failure
 */
public int
unq_move(string str)
{
    string	vb = QVB,
		room;
    if (vb == "east")
    {
	write("You step carefully out onto the stones.\n");
	TP->move_living("east", STONES);
	return 1;
    }
    return ::unq_move(str);
} /* unq_move */


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

    desc = BSN("The wide flat stones provide an easy route across "+
	       "the Anduin.");

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
 * Function name:	do_enter
 * Description	:	handle attempts to enter fissure/opening
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 */
public int
do_enter(string arg)
{
    if (arg == "fissure" ||
	arg == "narrow fissure" ||
	arg == "opening" ||
	arg == "good-sized opening" ||
	arg == "large cave" ||
	arg == "cave")
    {
	WRITE("You slip through the narrow fissure and enter "+
	    "a large cave.");
	TP->move_living("west", CAVE);	/* well, sort of west :-) */
	return 1;
    }
    NF0("Enter what?\n");
} /* do_enter */


/*
 * Function name:	dig_results
 * Description	:	give results of digging
 * Arguments	:	object digger -- the person digging
 */
public void
dig_results(object digger)
{
    object	ob;
    string	shortstr;

    if (!Stuffhere)
    {
	tell_object(digger, "You find nothing buried in the sand.\n");
	return;
    }

    Stuffhere = 0;
    /* 4 chances each of useless items
     * 2 chances each of moderately useful item
     * 1 chances each of jewelery
     */
    switch (random(21))
    {
    case 0..3:
	ob = clone_object(OBJ_DIR + "nail");
	break;
    case 4..7:
	ob = clone_object(ENTWASH_DIR + "obj/bone");
	break;
    case 8..11:
	ob = clone_object(RIVER_ANDUIN_DIR + "obj/rustykey");
	break;
    case 12..13:
	ob = clone_object(WEP_DIR + "ivknife");
	break;
    case 14..15:
	ob = clone_object(WEP_DIR + "woodknife");
	break;
    case 16..17:
	ob = clone_object(OBJ_DIR + "herbcord");
	break;
    case 18:
	ob = clone_object(OBJ_DIR + "orc_loot/bracelet");
	break;
    case 19:
	ob = clone_object(OBJ_DIR + "orc_loot/pin");
	break;
    case 20:
	ob = clone_object(OBJ_DIR + "goldring");
	break;
    }

    shortstr = ob->short();
    if (shortstr[0..1] != "a " &&
	shortstr[0..2] != "an ")
    {
	shortstr = LANG_ADDART(shortstr);
    }
    tell_object(digger,
	"You find "+shortstr+" buried in the sand.\n");
    tell_room(TO,
	QCTNAME(digger)+" finds something buried in the sand.\n",
	digger);
    if (ob->move(digger))
    {
	tell_object(digger, "Oops! You dropped it.\n");
	tell_room(TO,
	    QCTNAME(digger)+" drops "+shortstr+".\n",
	    digger);
	ob->move(TO, 1);
    }
} /* dig_results */
