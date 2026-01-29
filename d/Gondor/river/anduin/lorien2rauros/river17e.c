/*
 * /d/Gondor/river/anduin/lorien2rauros/river17e.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * day 8 campsite, small shallow bay .5 miles upstream of sarn gebir
 *
 */

#pragma strict_types

inherit "/d/Gondor/river/anduin/anduin_onwater";
inherit "/d/Gondor/common/lib/tod_descs";

#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/std/water/onwater.h"
#include <adverbs.h>
#include "../anduin.h"

/* prototypes */
public void	create_anduin_onwater();
public void	init();
public int	do_listen(string arg);
public int	exa_noise_icky(string arg);
public string	scenery_msgs(object ob, string vb, string dir);


/*
 * Function name:	create_anduin_onwater
 * Description	:	set up the room
 */
public void
create_anduin_onwater()
{
    add_prop(OBJ_S_WIZINFO,
	BSN("day 8 campsite, small shallow bay .5 miles upstream "+
	    "of sarn gebir, about 337 miles downstream of silverlode"));
    set_short("on the east side of the River Anduin");

    /* use tod_descs to append time-of-day descriptions to long
     * and to handle sky items
     */
    set_tod_long("The waters churn violently south past rugged hill "+
	"country. On the far west side of the river there appears "+
	"to be a shallow bay, while to the east the bank rises "+
	"steeply away from the river. A steady rumbling noise "+
	"comes from downstream.");
    set_tod_landname("the Emyn Muil");
    set_tod_landtype("river");
    set_tod_prependshort(1);
    set_long(tod_descs);
    add_item( ({ "sky", "sun", "moon", "star", "stars" }), tod_descs );


    set_watertype("river");
    set_watername("River Anduin");
    set_waterrefs( ({ "great river", "waters", "water", "river", "anduin",
	"river anduin", "anduin river" }) );
    set_downstreamdir( ({ "south", "southwest" }) );
    set_upstreamdir( ({ "north", "northwest" }) );
    set_currentstr( ({ 7, 7 }) ); /* rough */ 
    set_depth(305); /* 10 feet */
    set_rock_density(ROCKY);

    add_exit("river16e", "north");
    set_distance("north", 12);
    add_exit("river16w", "northwest");
    set_distance("northwest", 12);
    add_exit("river18", "south");
    add_exit("river18", "southwest");
    add_exit("river17w", "west");
    add_exit("riverbottom17e", "down");
    /* no shore rooms for now */

    add_item( ({ "great river", "waters", "water", "river anduin",
	"anduin river", "anduin", "river" }),
	BSN("The waters are moving very swiftly. They "+
	    "froth and boil as they roll over half-submerged rocks."));
    add_item( ({ "jagged rocks", "rocky shoals", "shoals", "rock", "rocks" }),
	BSN("The flowing waters are roiled by large rocks which "+
	    "jut up from beneath the waves."));
    add_item( ({ "emyn muil", "hill country", "country", "hills",
	"rugged country", "rugged hill country", "land", }),
	BSN("Beyond the steep shores and low cliffs, there rise "+
	    "high ridges crowned with wind-writhen firs. "+
	    "The Emyn Muil is a rugged land."));
    add_item( ({ "tree", "trees", "fir tree", "fir trees", "gnarled fir",
	"gnarled fir tree", "gnarled firs", "gnarled fir trees",
	"wind-writhen fir", "fir", "wind-writhen firs", "firs",
	"wind-scoured ridge", "high ridge", "ridge",
	"wind-scoured ridges", "high ridges", "ridges", }),
	BSN("Wind-scoured ridges, crowned with gnarled fir trees, "+
	    "loom high on either side."));
    add_item( ({ "shore", "shores", "river bank", "river banks",
	"bank", "banks", }),
	BSN("The west shore appears to decline slightly into a "+
	"shallow bay, but the east shore stretches steeply upwards."));
    add_item( ({ "eastern side", "eastern shore", "eastern bank",
    	"east side", "east shore", "east bank", }),
	BSN("The steep, thorny shore rises steeply away from the river."));
    add_item( ({ "far western side", "western side", "western shore",
	"western bank", "far west side", "west side", "west shore",
	"west bank", }),
	BSN("The west shore dips to a shallow bay."));
    add_item( ({ "shallow bay", "bay" }),
	BSN("From here, little of the bay is visible."));
    add_item( ({ "low cliff", "low cliffs", "crumbling cliff",
	"crumbling cliffs", "cliff", "cliffs", }),
	BSN("Low cliffs, dotted with slender stone chimneys, rise "+
	    "just beyond the shores."));
    add_item( ({ "slender chimney", "slender chimneys", 
	"fingers", "finger", "tall finger", "tall fingers",
	"fingers of stone", "finger of stone", "tall finger of stone",
	"tall fingers of stone", "chimney", "chimneys", }),
	BSN("The chimneys are tall fingers of stone, covered "+
	    "with ivy."));
    add_item( ({ "vine", "vines", "ivy" }),
	BSN("Dark-leaved vines cling to the stone chimneys."));
    add_item( ({ "stone", "stones" }),
	BSN("The stone is gray and weathered."));
    add_item( ({ "thicket", "thickets", "brake", "brakes",
	"thorn", "thorns", "bramble", "brambles", }),
	BSN("Tangled brambles cloak the east shore."));
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
	WRITE("To the south are rumoured to be the deadly rapids "+
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
	WRITE("To the south are rumoured to be the deadly rapids "+
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


/*
 * Function name:	scenery_msgs
 * Description	:	mask parent to give the last warning msg
 *			if people or boats are going downstream.
 * Arguments	:	object ob -- who/what is moving
 *			string vb -- "swim", "wade", "row", "dive", "wash"
 *			string dir -- the direction of movement
 */
public string
scenery_msgs(object ob, string vb, string dir)
{
    string desc;

    if (dir == "south" ||
	dir == "southwest" ||
	dir == "downstream")
    {
	desc = BSN("The river narrows to a rock-filled channel "+
	           "and the violence of the water grows terrifying.");
    }
    else
    {
	desc = "";
    }
    return desc;
} /* scenery_msgs */
