/*
 * /d/Gondor/river/anduin/lorien2rauros/bay17.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * day 8 campsite, small shallow bay .5 miles upstream of sarn gebir
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/water/onwater";
inherit "/d/Gondor/common/lib/tod_descs";

#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/std/water/onwater.h"
#include <adverbs.h>
#include "../anduin.h"

/* prototypes */
public void	create_onwater();
public void	init();
public int	do_listen(string arg);
public int	exa_noise_icky(string arg);


/*
 * Function name:	create_onwater
 * Description	:	set up the room
 */
public void
create_onwater()
{
    add_prop(OBJ_S_WIZINFO,
	BSN("day 8 campsite, small shallow bay .5 miles upstream "+
	    "of sarn gebir, about 337 miles downstream of silverlode"));
    set_short("a calm, shallow bay");

    set_tod_long("A few low trees grow close to the water "+
	"and behind them rises a steep rocky bank. To the east lies "+
	"the Great River, and from somewhere downstream there comes "+
	"a steady rumbling noise.");
    set_tod_landname("the Emyn Muil");
    set_tod_landtype("bay");
    set_tod_prependshort(1);
    set_long(tod_descs);
    add_item( ({ "sky", "sun", "moon", "star", "stars" }), tod_descs );

    set_watertype("bay");
    set_watername("shallow bay");
    set_waterrefs( ({ "small bay", "small shallow bay", "shallow bay",
	"waters", "water", }) );
    set_currentstr(0);
    set_depth(MIN_SWIM_DEPTH);
    set_rock_density(0);

    add_exit("river17w", "east");
    add_exit("beach17w", "west");
    set_no_exit_msg( ({ "northeast", "north", "northwest",
	"southwest", "south", "southeast" }),
	BSN("You wade around the shallow bay."));

    add_item( ({ "waters", "water", "calm shallow bay", "shallow bay",
	"bay", }),
	BSN("The bay is quite calm, and not very deep."));
    add_item( ({ "ground", "bottom", "river bottom", "bay bottom",
	"bottom of bay" }),
	BSN("Beneath the shallow waters is a firm bottom of gray stone."));
    add_item( ({ "gray stones", "gray stone", "stones", "stone" }),
	BSN("The same gray stone forms both river bottom and shore."));
    add_item( ({ "great river", "river anduin", "anduin river",
	"anduin", "river" }),
	BSN("Just east of the bay, the broad swift waters of the "+
	    "Anduin flow south."));
    add_item( ({ "rocky slope", "slope", "shore", "shores", 
	"river bank", "river banks", "bank", "banks", "western shore",
	"western bank", "west shore", "west bank", }),
	BSN("Beyond the trees, a rocky slope, cloaked "+
	    "with brambles, rises towards low cliffs."));
    add_item( ({ "steep shore", "eastern shore", "eastern bank",
    	"east shore", "east bank", }),
	BSN("From this distance, all that may be seen is a steep shore."));
    add_item( ({ "horizon", "low cliff", "low cliffs", "weathered cliff",
	"weathered cliffs", "cliff", "cliffs", }),
	BSN("Low cliffs, dotted with slender stone chimneys, march "+
	    "along the horizon."));
    add_item( ({ "slender stone chimney", "stone chimney",
    	"slender chimney", "chimney", "slender stone chimneys",
	"stone chimneys", "slender chimneys", "chimneys" }),
	BSN("Slender chimneys of stone rise among the cliffs."));
    add_item( ({ "good-sized boulder", "good-sized boulders",
    	"boulder", "boulders", "rock", "rocks", }),
	BSN("Good-sized boulders are tumbled about the slope."));
    add_item( ({ "bramble", "brambles" }),
	BSN("Brambles grow thickly on the steep slope of the western shore."));
    add_item( ({ "hills", "emyn muil", "land", "country" }),
	BSN("The rugged land look harsh and unwelcoming."));
    add_item( ({ "edge", "low scrubby tree", "low scrubby trees",
	"low tree", "low trees", "tree", "trees" }),
	BSN("Along the edge of the water grow low scrubby trees, "+
	    "their gnarled roots clinging to the rocky slope "+
	    "and dipping thirstily into the bay."));
    add_item( ({ "ancient finger", "ancient fingers", "finger",
	"fingers", "gnarled root", "gnarled roots", "root", "roots", }),
	BSN("The roots resemble ancient fingers, painfully "+
	   "twisted and knotted."));

    add_cmd_item( ({ "low scrubby tree", "low scrubby trees",
	"low tree", "low trees", "tree", "trees" }),
	"climb",
	BSN("You cannot reach the trees from here."));
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
	WRITE("Downstream are rumoured to be the deadly rapids "+
	    "of Sarn Gebir, through which none have ever passed alive. "+
	    "Probably it is the noise of the rapids you hear.");
	return 1;
    }

    arg = LOW(arg);
    if (arg == "." ||
        strlen(FULL_ADVERB(arg)))
    {
         return 0;	/* fall thru to soul */
    }

    if (parse_command(arg, ({}),
		"[to] [the] [steady] [rumble] / [rumbling] %s", tmpstr) &&
        (tmpstr == "downstream" ||
	 tmpstr == "" ||
         tmpstr == "sound" ||
         tmpstr == "noise" ||
         tmpstr == "rapids" ||
         tmpstr == "sarn gebir"))
    {
	WRITE("Downstream are rumoured to be the deadly rapids "+
	    "of Sarn Gebir, through which none have ever passed alive. "+
	    "Probably it is the noise of the rapids you hear.");
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
		"[at] [the] [steady] [rumble] / [rumbling] %s", tmpstr) &&
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
