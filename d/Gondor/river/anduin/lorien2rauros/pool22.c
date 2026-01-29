/*
 * /d/Gondor/river/anduin/lorien2rauros/pool22.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * small pool at southern end of portage trail, 1 mile
 * below sarn gebir.
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/water/onwater";
inherit "/d/Gondor/common/lib/tod_descs";

#include <composite.h>		/* for COMPOSITE_LIVE */
#include <filter_funs.h>	/* for FILTER_LIVE */
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/std/water/onwater.h"
#include <adverbs.h>
#include "../anduin.h"

#define	PIERWEST	(LORIEN_TO_RAUROS_DIR+"pierwest")
#define	PIEREAST	(LORIEN_TO_RAUROS_DIR+"piereast")

/* prototypes */
public void	create_onwater();
public void	init();
public int	do_listen(string arg);
public int	exa_noise_icky(string arg);
public string	exa_pier();
public int	do_climb(string arg);
public int	unq_move(string str);

static object	PierW,
		PierE;		/* the pier rooms */


/*
 * Function name:	create_onwater
 * Description	:	set up the room
 */
public void
create_onwater()
{
    FIX_EUID;	/* because we may load PIERWEST and PIEREAST */

    add_prop(OBJ_S_WIZINFO,
	BSN("1 mile below sarn gebir, 339 miles downstream "+
	    "from the silverlode."));
    set_short("a shallow pool");

    set_tod_long(
	"The waters of this pool are calm and quite shallow. "+
	"A low pier of stone runs along the south edge of the pool "+
	"and protrudes some way into the Anduin to the east. Along "+
	"the shore, the pier curves northwest to form a low stony beach.");
    set_tod_landname("the Emyn Muil");
    set_tod_landtype("pool");
    set_long(tod_descs);
    add_item( ({ "sky", "sun", "moon", "star", "stars" }), tod_descs );

    set_watertype("pool");
    set_watername("shallow pool");
    set_waterrefs( ({ "shallow pool", "waters", "water", }) );
    set_currentstr(0);
    set_depth(MIN_SWIM_DEPTH);
    set_rock_density(0);

    add_exit("river22", "east");
    add_exit("pierwest", "south");
    add_exit("pierwest", "southwest");
    add_exit("piereast", "southeast");
    add_exit("beach22w", "west");

    add_item( ({ "waters", "water", }),
	BSN("The shallow waters of the pool are calm and clear."));
    add_item( ({ "shallow pool", "shallow pool", "pool", }),
	BSN("The shallow pool seems to have been scooped in the river-side "+
	"by the swirl of the river against the stone pier."));
    add_item( ({ "ground", "bottom", "river bottom", "pool bottom",
	"bottom of pool" }),
	BSN("Beneath the shallow waters is a firm bottom of gray stone."));
    add_item( ({ "gray stones", "gray stone", "stones", "stone" }),
	BSN("The stone is gray, and darkened with river mist."));
    add_item( ({ "fine mist", "river mist", "mist" }),
	BSN("A fine mist rises from the river."));
    add_item( ({ "great river", "river anduin", "anduin river",
	"anduin", "river" }),
	BSN("The Great River swirls against the stone pier as it "+
	    "races south between the cliffs of the Emyn Muil."));
    add_item( ({ "eastern shore", "eastern bank", "eastern cliff",
	"eastern cliffs", "east shore", "east bank", "east cliff",
	"east cliffs" }),
	BSN("The cliffs of the east shore are somewhat obscured by mist."));
    add_item( ({ "river-side", "shore", "shores", "river bank",
	"river banks", "bank", "banks", "western shore",
	"western bank", "west shore", "west bank", }),
	BSN("Steep cliffs line both shores. To the west, there "+
	    "appears to be a cleft leading inland."));
    add_item( ({ "wall", "walls", "wall of gray stone", 
	"walls of gray stone", "cliff", "cliffs", }),
	BSN("Gray stone rises almost vertically on both sides "+
	    "of the river. There appears to be an opening in the "+
	    "cliff on the west shore."));
    add_item( ({ "gnarled fir", "gnarled firs", "fir", "firs",
	"tree", "trees" }),
	BSN("High above the water, a few gnarled firs cling "+
	    "to the cliffs."));
    add_item( ({ "western cliff", "western cliffs", "west cliff",
	"west cliffs" }),
	BSN("The shore rises sheer into a gray cliff, pierced by "+
	"a narrow trail."));
    add_item( ({ "inland", "cleft", "opening", "narrow trail",
	"trail", }),
	BSN("A narrow trail leads west from the stony beach into "+
	    "a cleft in the wall of gray stone."));
    add_item( ({ "low stony beach", "low beach", "stony beach", "beach" }),
	BSN("A low beach of gray stone runs along the western "+
	    "edge of the pool."));
    add_item( ({ "emyn muil" }),
	BSN("The cliffs of the Emyn Muil rise sheer and unwelcoming."));
    add_item( ({ "long finger of stone", "finger of stone", "long finger",
	"stone finger", "finger", "low pier of gray stone",
	"low pier of stone", "low pier", "stone pier", "pier", }),
	exa_pier);
} /* create_onwater */



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
	WRITE("You hear a steady bass rumble coming from upstream.");
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
         tmpstr == "sound" ||
         tmpstr == "noise" ||
         tmpstr == "" ||
         tmpstr == "rapids" ||
         tmpstr == "sarn gebir"))
    {
	WRITE("You hear a steady bass rumble coming from upstream.");
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
	    (tmpstr == "" ||
             tmpstr == "noise" ||
             tmpstr == "sound"))
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

    desc = "The pier juts into the Anduin like a long finger, "+
	   "pointing the way east.\n";

    if (!objectp(PierW))
    {
	PIERWEST->short();
	PierW = find_object(PIERWEST);
    }
    if (!objectp(PierE))
    {
	PIEREAST->short();
	PierE = find_object(PIEREAST);
    }
    live_on_pier = FILTER_LIVE(all_inventory(PierW) + all_inventory(PierE));
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
	if (QVB != "southeast")
	{
	    WRITE("You climb onto the stone pier.");
	    tp->move_living("onto the pier", PIERWEST);
	}
	else
	{
	    WRITE("You climb out onto the east end of the stone pier.");
	    tp->move_living("onto the pier", PIEREAST);
	}
	return 1;
    }
    NF0("Climb what?\n");
} /* do_climb */


/*
 * Function name:	unq_move
 * Description	:	mask parent so that "south" behaves like
 *			"climb pier"
 * Arguments	:	string str - the command line argument.
 * Returns	:	int 1/0.
 */
public int
unq_move(string str)
{
    string	vb = QVB;

    if (vb == "south" ||
	vb == "southwest" ||
	vb == "southeast")
    {
	return do_climb("pier");
    }
    return ::unq_move(str);
} /* unq_move */
