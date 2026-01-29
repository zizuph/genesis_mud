/*
 * /d/Gondor/river/anduin/lorien2rauros/fishcamp_n.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * north end of Beornings fishcamp, adjacent to crossing
 *
 * TBD: find some likely fishcamp junk in sand when dig
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/water/shore_room";
inherit "/d/Gondor/common/lib/tod_descs";
inherit "/d/Gondor/common/lib/drink_water";
inherit "/d/Gondor/common/lib/dig";

#include <cmdparse.h>		/* for NORMAL_ACCESS */
#include <composite.h>		/* for COMPOSITE_WORDS */
#include <filter_funs.h>	/* for FILTER_LIVE */
#include <stdproperties.h>	/* for OBJ_I_* */
#include <wa_types.h>		/* for W_SLASH */
#include "/d/Gondor/defs.h"	/* always */
#include "fishcamp.h"

#define	RIVER	(CARROCK_TO_LORIEN_DIR + "river00")
#define	STONES	(CARROCK_TO_LORIEN_DIR + "carrock_stones")

#define N_RESET_FISH    5

#define GETTABLE_ITEMS \
    ({ "small bone", "fish bone", "bone", "small bones", "bones", \
       "fish bones", "twine", "snippet", "snippets", "snippet of twine", \
       "snippets of twine", "horizontal strip of wood", "horizontal strip", \
       "horizontal strips of wood", "horizontal strips", \
       "slender strip of wood", "slender strip", "strip", \
       "slender strips of wood", "slender strips", "strips", })



/* prototypes */
public void	create_shore_room();
public void	reset_room();
public void	init();
public int	unq_move(string str);
public void	leave_inv(object ob, object dest);
public void	dig_results(object digger);
public string	exa_stones();
public int	take_stuff(string arg);
public int	cut_fish(string arg);
public int	parse_fish(string arg);

static int	Nfish;
static object	Stones;		/* the stones room */


/*
 * Function name:	create_shore_room
 * Description	:	set up the beach
 */
public void
create_shore_room()
{
    FIX_EUID;	/* will clone items */
    set_short("wide sandy beach");

    /* use tod_descs to append time-of-day descriptions to long
     * and to handle sky items
     */
    set_tod_long(
	"A wide strip of sand borders the Anduin, where a line of " +
	"flat stones leads across the river towards a great rock in " +
	"mid-stream. At the east edge of the sand rises a great " +
	"rack, holding what must be hundreds of fish. Beyond the " +
	"rack endless plains of grass stretch away to the horizon.");
    set_tod_landname("the vale of Anduin");
    set_tod_landtype("beach");
    set_long(tod_descs);
    add_item( ({ "sky", "sun", "moon", "star", "stars" }), tod_descs );

    set_water("west",
	({ "ford", "great river", "waters", "water", "river", "anduin",
	"river anduin", "anduin river" }) );

    /* walking in deep sand is tiring */
    add_exit("river00", "west", 0, 5, 1);
    add_exit("fishcamp_s", "southwest", 0, 5);

    set_no_exit_msg("northwest",
	"You wander idly along the beach.\n");
    set_no_exit_msg( ({ "northeast", "north", "east",
	"south", "southeast", }),
	BSN("You wander for a while among the tall grasses, but " +
	    "soon become disoriented and return to the beach."));

    add_item( ({ "great river", "river anduin", "anduin river",
	"anduin", "river", "waters", "water", }),
	&exa_water(RIVER,
	    BSN("The Anduin, wide and shallow, gurgles and froths " +
	    "as it splashes around the stones. To the southwest, " +
	    "it deepens as it flows past the Carrock.")));

    add_item( ({ "beach", "wide strip of sand", "strip of sand",
	"narrow strip", "strip", }),
	BSN("The beach is just a flat strip of sand, empty " +
	    "except for the fish rack."));
    add_item( ({ "ground", "coarse grey sand", "coarse sand",
        "grey sand", "sand", }),
        BSN("Coarse sand, light grey in colour, is littered with " +
            "fish bones and snippets of twine."));
    add_item( ({ "small bone", "fish bone", "bone", "small bones",
        "fish bones", "bones" }),
        "Small bones, bare of all flesh, are scattered across the sand.\n");
    add_item( ({ "snippet", "snippets", "snippet of twine",
        "snippets of twine", }),
        "None of the snippets of twine is longer than an inch or so.\n");
    add_item( ({ "fish rack", "drying rack", "large rack", "rack", }),
        BSN("The drying rack is perhaps twelve feet tall and twenty feet " +
	    "wide. It consists of slender strips of wood running " +
	    "horizontally, between supporting timbers at either end. " +
            "Hundreds of fish are tied by the tail to these strips."));
    add_item( ({ "horizontal strip of wood", "horizontal strip",
        "horizontal strips of wood", "horizontal strips",
        "slender strip of wood", "slender strip", "strip",
        "slender strips of wood", "slender strips", "strips", }),
        BSN("The strips are not quite wrist-thick, and " +
            "are spaced a couple of feet apart. They are thickly " +
            "filled with drying fish."));
    add_item( ({ "supporting timber", "supporting timbers", "timber",
        "timbers", }),
        BSN("The supporting timbers, considerably thicker than " +
            "the horizontal strips, are firmly set into the sand."));
    add_item( ({ "tail", "fish tail", "drying fish", "fish on rack", "fish", }),
        "Each fish hangs head-down, tied to the rack by its tail.\n");
    add_item( ({ "twine", }),
        BSN("Fish are tied with twine to the drying rack, and snippets " +
            "of twine lie underfoot."));
    add_item( ({ "knot", "knots", }),
        "The knots attaching fish to the drying rack are very tight.\n");

    add_item( ({ "west horizon", "western horizon", "western bank",
	"west bank", "far shore", "far side",
	"far side of river", "western shore", "west shore" }),
	BSN("The far shore, beyond the rock, is cloaked with " +
	    "tall grasses."));
    add_item( ({ "great rock", "rock", "great hill", "great hill of stone",
	"hill of stone", "hill", "carrock", }),
	BSN("The Carrock, a great hill of stone, juts up in the " +
	    "middle of the Anduin."));
    add_item( ({ "this shore", "this side", "this side of river",
	"shore", "shores", "eastern bank", "east bank", "eastern shore",
	"east shore" }),
	BSN("On this side of the river, the land is a flat, green " +
	    "plain of grass."));
    add_item( ({ "east horizon", "eastern horizon", "horizon",
	"flat green plain", "flat green plains", "plain", "plains",
	"endless plain", "endless plains", "grassland", "grasslands", }),
	BSN("Tall grasses stretch away from the river as far as the eye " +
	    "can see."));
    add_item( ({ "tall grass", "tall grasses", "grasses", "grass", }),
	BSN("Tall grasses, green and swaying lightly with passing " +
	    "breezes, cover the land."));
    add_item( ({ "carrock ford", "ford", "line", "huge flat stone",
	"huge stone", "flat stone", "stone", "huge flat stones",
	"huge stones", "flat stones", "stones", }),
	exa_stones);
    add_item( ({ "hilltop", "hill top", "top", }),
	BSN("The hill is quite flat on top."));

    add_cmd_item( ({ "knot", "knots", "drying fish", "fish", }),
        "untie",
        BSN("The knots are too tight -- try as you might, you " +
            "cannot untie a fish from the drying rack."));
    add_cmd_item( ({ "fish rack", "drying rack", "large rack", "rack", }),
        "climb",
        BSN("The rack is too thickly filled with fish for you to " +
            "be able to climb safely."));
    set_drink_from( ({ "ford", "great river", "river anduin", "anduin river",
	"anduin", "river", }) );

    set_dig_pattern("[in] [the] [coarse] [brown] [grey] " +
	"[and] [brown] 'sand' / 'here'");
    set_dig_message("in the sand");

    reset_room();

} /* create_shore_room */


/*
 * Function name:	reset_room
 * Descripion:		reset # of fish available
 */
public void
reset_room()
{
    Nfish = N_RESET_FISH + random(N_RESET_FISH);
} /* reset_room */


/*
 * Function name:	init
 * Description	:	add drink verb and "dig"
 */
public void
init()
{
    ::init();
    init_drink();
    add_action(dig_here,	"dig");
    add_action(take_stuff,	"take");
    add_action(take_stuff,	"get");
    add_action(take_stuff,	"pick");
    add_action(cut_fish,	"cut");
} /* init */


/*
 * Function name:	unq_move
 * Description	:	mask parent's unq_move() so that "west" moves us
 *			onto the stones, but "swim" into the river.
 * Arguments	:	string str - the command line argument.
 * Returns	:	1 on success, 0 o failure
 */
public int
unq_move(string str)
{
    string	vb = QVB,
		room;
    if (vb == "west")
    {
	write("You step carefully out onto the stones.\n");
	TP->move_living("west", STONES);
	return 1;
    }
    return ::unq_move(str);
} /* unq_move */


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
 * Function name:	dig_results
 * Description	:	give results of digging
 * Arguments	:	object digger -- the person digging
 */
public void
dig_results(object digger)
{
    tell_object(digger, "You find nothing buried in the sand.\n");
} /* dig_results */


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

    desc = BSN("Huge stones have been set in the river, " +
	    "making it possible to cross to the Carrock dryshod.");

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
	desc += BSN(live_on_stones[0]->query_Art_name(TP) +
		" is standing on a stone in the ford.");
	break;
    default:
	desc += BSN(CAP(COMPOSITE_LIVE(live_on_stones)) +
		" are standing on stones in the ford.");
    }
    return desc;
} /* exa_stones */


/*
 * Function name:	take_stuff
 * Description:		respond to attempts to take items
 * Arguments:		string arg -- what they tried for.
 * Returns:		int -- 1 if we handle it, 0 not
 */
public int
take_stuff(string arg)
{
    mixed	*targets;
    string	tmpstr,
		vb = QVB;

    if (!strlen(arg))
    {
        return 0;
    }
    arg = LOW(arg);
    if (parse_command(arg, all_inventory(TO), "%i", targets) &&
        sizeof(targets = NORMAL_ACCESS(targets, 0, 0)))
    {
        /* there's such an object in this room */
        return 0;
    }

    if (parse_fish(arg))
    {
        WRITE("The knots are too tight -- try as you might, you " +
            "cannot untie a fish from the drying rack.");
	return 1;
    }

    if (member_array(arg, GETTABLE_ITEMS) >= 0)
    {
	write("You don't find any of the " + arg + " worth taking.\n");
	return 1;
    }
    return 0;
} /* take_stuff */


/*
 * Function name:	cut_fish
 * Description	:	respond to attempts to cut fish from rack
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 if we recognize the arg, 0 if not
 *
 * TBD: handle as search-like task?
 */
public int
cut_fish(string arg)
{
    object	fish, *weaps;
    int		s;

    if (!strlen(arg) ||
	!parse_fish(LOW(arg)))
    {
	NF0("Cut what?\n");
    }

    s = sizeof(weaps = TP->query_weapon(-1));
    if (!s)
    {
        WRITE("You cannot cut a fish from the drying rack using " +
            "your bare hands.");
	return 1;
    }

    if (!(weaps[0]->query_dt() & W_SLASH) &&
	(s == 1 ||
	 !(weaps[1]->query_dt() & W_SLASH)))
    {
        WRITE("You cannot cut a fish from the drying rack using " +
            COMPOSITE_DEAD(weaps) + "."); 
	return 1;
    }

    if (Nfish <= 0)
    {
        WRITE("None of the fish look very appetizing, so you " +
            "leave them on the drying rack.");
	return 1;
    }

    --Nfish;
    fish = clone_object(FISH_FILE);
    write("You cut a fish from the drying rack.\n");
    SAY(" cuts a fish from the drying rack.");
    if (fish->move(TP))
    {
        write("Oops, you dropped it.\n");
        SAY(" drops a fish.");
        fish->move(TO);
    }
    return 1;
} /* cut_fish */


/*
 * Function name:	parse_fish
 * Description	:	parse the player's arg to see if it
 *			refers to fish on the rack
 * Arguments	:	string arg -- the lowercase arg
 * Returns	:	1 if refers to fish, 0 if not
 */
public int
parse_fish(string arg)
{
    string	tmpstr;

    if (!strlen(arg))
    {
	return 0;
    }
    if (!parse_command(arg, ({}),
	    "[a] [the] [drying] [dry] 'fish' / 'knot' / " +
	    "'knots' / 'twine' %s", tmpstr))
    {
	return 0;
    }
    if (strlen(tmpstr) &&
	!parse_command(tmpstr, ({}),
	    "'from' / 'off' / 'on' [the] [large] [drying] " +
	    "'rack' / 'strip' / 'strips'"))
    {
	return 0;
    }
    return 1;
} /* parse_fish */
