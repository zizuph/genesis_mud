/*
 * /d/Gondor/river/anduin/lorien2rauros/river22.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * 1 mile below sarn gebir
 *
 */

#pragma strict_types

inherit "/d/Gondor/river/anduin/anduin_onwater";
inherit "/d/Gondor/common/lib/tod_descs";


#include <composite.h>		/* for COMPOSITE_LIVE */
#include <filter_funs.h>	/* for FILTER_LIVE */
#include <stdproperties.h>	/* for OBJ_S_WIZINFO, etc */
#include "/d/Gondor/defs.h"
#include "/d/Gondor/std/water/onwater.h"
#include <adverbs.h>
#include "../anduin.h"

#define	PIER	(LORIEN_TO_RAUROS_DIR+"piereast")
#define	MAX_ENCUMBERANCE	80

/* prototypes */
public void	create_anduin_onwater();
public void	init();
public int	no_way();
public string	scenery_msgs(object ob, string vb, string dir);
public int	do_listen(string arg);
public int	exa_noise_icky(string arg);
public string	exa_pier();
public int	do_climb(string arg);
public int	unq_move(string str);

static object	Pier;		/* the pier room */


/*
 * Function name:	create_anduin_onwater
 * Description	:	set up the room
 */
public void
create_anduin_onwater()
{
    add_prop(OBJ_S_WIZINFO,
	BSN("1 mile below sarn gebir, 339 miles downstream from the silverlode."));
    set_short("on the River Anduin");

    /* use tod_descs to append time-of-day descriptions to long
     * and to handle sky items
     */
    set_tod_long(
	"The waters rush and foam over the stony teeth of Sarn Gebir "+
	"to the north and, swirling past a "+
	"low pier of gray stone, plunge south between gray cliffs.");
    set_tod_landname("the Emyn Muil");
    set_tod_landtype("river");
    set_tod_prependshort(1);
    set_long(tod_descs);
    add_item( ({ "sky", "sun", "moon", "star", "stars" }), tod_descs );

    set_watertype("river");
    set_watername("River Anduin");
    set_waterrefs( ({ "great river", "waters", "water", "river", "anduin",
	"river anduin", "anduin river" }) );
    set_downstreamdir("south");
    set_upstreamdir("north");
    set_currentstr(6);	/* rapid */
    set_depth(610);	/* 20 feet */
    /* no rocks */

    add_exit("river21", "north", no_way);
    add_exit("river23", "south");
    set_distance("south", 20);
    add_exit("pool22", "west");
    add_exit("riverbottom22", "down");
    /* no shore rooms */

    add_item( ({ "great river", "waters", "water", "river anduin",
	"anduin river", "anduin", "river" }),
	BSN("The river swirls against a long finger of stone, then "+
	    "races south between the cliffs of the Emyn Muil."));
    add_item( ({ "sarn gebir", "rapids" }), 
	BSN("Just upstream the waters churn violently through "+
	    "the rapids of Sarn Gebir."));
    add_item( ({ "water upstream", "upstream water", "waters upstream",
	"upstream waters", "teeth", "stony teeth", "jagged rock",
	"jagged rocks", "rock", "rocks" }),
	BSN("The waters upstream crash against jagged rocks that "+
	    "jut up from the river like stony teeth."));
    add_item( ({ "shore", "shores", "river bank", "river banks",
	"bank", "banks", }),
	BSN("The shores are sheer cliffs, but to the west "+
	"the currents have carved out a small pool."));
    add_item( ({ "eastern side", "eastern shore", "eastern bank", 
    	"east side", "east shore", "east bank",  }),
	BSN("To the east, the land rises straight from the river "+
	"in a sheer stone face."));
    add_item( ({ "sheer stone face", "stone face", "face",
	"great rocky sides", "rocky sides", "sides",  "wide ravine",
	"ravine", "sheer cliff", "sheer cliffs", "cliff", "cliffs", }),
	BSN("The cliffs enclose a wide ravine, with great rocky sides "+
	    "to which cling, upon shelves and in narrow crevices, "+
	    "a few thrawn trees. The Great River plunges "+
	    "south down the center of the ravine."));
    add_item( ({ "shelf", "shelves", "narrow crevice", "crevice",
	"narrow crevices", "crevices" }),
	BSN("High above the water, a few gnarled firs cling "+
	    "to the sides of the ravine."));
    add_item( ({ "gnarled fir", "gnarled firs", "fir", "firs",
	"wind-twisted fir", "wind-twisted firs",
	"thrawn tree", "thrawn trees", "tree", "trees" }),
	BSN("The wind-twisted firs have a precarious purchase "+
	    "on the cliffs."));
    add_item( ({ "western side", "western shore", "western bank",
	"west side", "west shore", "west bank", }),
	BSN("At the foot of the cliff along the west shore, a low "+
	    "pier of stone projects into the water past a shallow pool."));
    add_item( ({ "gray stone", "stone" }),
	BSN("Cliffs, pier and the rocks of Sarn Gebir all are the "+
	    "same gray stone."));
    add_item( ({ "fine mist", "river mist", "mist" }),
	BSN("A fine mist rises from the river."));
    add_item( ({ "emyn muil" }),
	BSN("The cliffs grow ever higher as the Great River races "+
	    "south into the Emyn Muil."));
    add_item( ({ "long finger of stone", "finger of stone", "long finger",
	"stone finger", "finger", "low pier of gray stone",
	"low pier of stone", "low pier", "stone pier", "pier", }),
	exa_pier);
    add_item( ({ "shallow pool", "pool" }),
	BSN("The pool seems to have been scooped in the river-side by "+
	"the water swirling down from Sarn Gebir against the stone pier. "+
	"It appears relatively sheltered, and not very deep."));
    
} /* create_anduin_onwater */


/*
 * Function name:	init
 * Description	:	add 'listen'
 */
public void
init()
{
    ::init();
    add_action(do_listen, "listen");
    add_action(exa_noise_icky, "exa");
    add_action(exa_noise_icky, "examine");
    add_action(exa_noise_icky, "look");
    add_action(do_climb, "climb");
} /* init */


/*
 * Function name:	no_way
 * Description	:	exit efunc to block attempts to swim north
 * Returns	:	1 -- exit always fails
 */
public int
no_way()
{
    string	vb;
    if (ENV(TP) == TO)
    {
	vb = "swim";
    }
    else
    {
	vb = QVB;	/* "row", "scull", "pole", ... */
    }
    WRITE("You attempt to "+vb+" upstream, but the current is "+
	"much too strong and you make no progress at all.");
    return 1;
} /* no_way */


/*
 * Function name:	scenery_msgs
 * Description	:	mask parent to give a "the channel narrows" msg
 *			if people or boats are going downstream.
 * Arguments	:	object ob -- who/what is moving
 *			string vb -- the verb used
 *			string dir -- the direction of movement
 */
public string
scenery_msgs(object ob, string vb, string dir)
{
    string desc;

    if (dir == "south" ||
	dir == "downstream")
    {
	desc = BSN("As you travel downstream, the channel "+
	           "narrows and the river grows more swift.");
    }
    else
    {
	desc = "";
    }
    return desc;
} /* scenery_msgs */


/*
 * Function name:	do_listen
 * Description	:	let 'em listen 
 *			XXX replace with gilmanor's when ready
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 on success or plausible failure,
 *			0 if we really really think they meant the
 *			soul command.
 */
public int
do_listen(string arg)
{
    string	tmpstr;

    if (!strlen(arg))
    {
	WRITE("You hear a steady bass rumble coming from the "+
	    "rapids upstream.");
	return 1;
    }

    arg = LOW(arg);
    if (arg == "." ||
        strlen(FULL_ADVERB(arg)))
    {
         return 0;	/* fall thru to soul */
    }

    if (parse_command(arg, ({}),
		      "[to] [the] [steady] [bass] "+
		      "[rumble] / [rumbling] %s", tmpstr) &&
        (tmpstr == "upstream" ||
         tmpstr == "noise" ||
         tmpstr == "sound" ||
         tmpstr == "" ||
         tmpstr == "rapids" ||
         tmpstr == "sarn gebir"))
    {
	WRITE("You hear a steady bass rumble coming from the "+
	    "rapids upstream.");
    }
    else
    {
	write("Listen to what?\n");
    }
    return 1;
} /* do_listen */


/*
 * Function name:	exa_noise_icky
 * Description	:	let them "exa noise" (*wince* *icky*)
 * Argument	:	string arg -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 *
 * this is an experiment. it's icky. i may take it out.
 * N.B. more limited matches here. i don't think "exa rapids" should
 * give the same response as "listen to rapids", even tho "exa rumbling"
 * behaves like "listen to rumbling".
 */
public int
exa_noise_icky(string arg)
{
    string 	tmpstr;
    if (strlen(arg))
    {
	if (parse_command(arg, ({}),
		      "[at] [the] [steady] [bass] "+
		      "[rumble] / [rumbling] %s", tmpstr) &&
            (tmpstr == "sound" ||
             tmpstr == "noise" ||
             tmpstr == ""))
	{
	    log_file("anduin", ctime(time())+" "+TP->query_name()+
		" examined '"+arg+"'.\n");
	    do_listen("");
	    return 1;
	}
    }
    return 0;
} /* exa_noise_icky */


/*
 * Function name:	exa_pier
 * Description	:	VBFC for the pier -- mention anyone standing there
 * Returns	:	the pier desc
 */
public string
exa_pier()
{
    object	*live_on_pier;
    string	desc;
    int		s;

    desc = "The waters swirl against a low pier of stone that "+
	   "juts out far into the river.\n";

    if (!objectp(Pier))
    {
	FIX_EUID;
	PIER->short();
	Pier = find_object(PIER);
    }
    live_on_pier = FILTER_LIVE(all_inventory(Pier));
    if (!TP->query_wiz_level())
    {
	/* assume that from this distance, cannot see hidden or invis */
	live_on_pier = filter(filter(live_on_pier,
	    &not() @ &->query_prop(OBJ_I_HIDE)),
	    &not() @ &->query_invis());
    }
    s = sizeof(live_on_pier);
    if (s)
    {
	desc += CAP(COMPOSITE_LIVE(live_on_pier))+
		(s == 1 ? " is " : " are ")+
		"standing on the pier.\n";
    }
    return desc;
} /* exa_pier */


/*
 * Function name:	do_climb
 * Description	:	handle attempts to climb on pier
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 */
public int
do_climb(string arg)
{
    object	tp = TP;

    if (strlen(arg) &&
	parse_command(arg, ({}), "[up] [on] / [onto] [the] "+
	    "[long] [low] [stone] 'pier'"))
    {
	if (tp->query_encumberance_weight() <= MAX_ENCUMBERANCE)
	{
	    WRITE("You climb onto the stone pier.");
	    tp->move_living("onto the pier", PIER);
	}
	else
	{
	    WRITE("You try to climb onto the stone pier, but "+
		"slip and fall back into the river.");
	    SAY(" tries to climb onto the stone pier, but "+
		"slips and falls back into the river.");
	}
	return 1;
    }
    NF0("Climb what?\n");
} /* do_climb */


/*
 * Function name:	unq_move
 * Description	:	mask parent so that "southwest" behaves like
 *			"climb pier"
 * Arguments	:	string str - the command line argument.
 * Returns	:	int 1/0.
 */
public int
unq_move(string str)
{
    if (QVB == "southwest")
    {
	return do_climb("pier");
    }
    return ::unq_move(str);
} /* unq_move */
