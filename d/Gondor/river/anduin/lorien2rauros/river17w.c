/*
 * /d/Gondor/river/anduin/lorien2rauros/river17w.c
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
    set_short("on the west side of the River Anduin");

    /* use tod_descs to append time-of-day descriptions to long
     * and to handle sky items
     */
    set_tod_long("Beneath wind-scoured hills, the Great River flows "+
	"south, foaming and boiling over jagged rocks, and a steady "+
	"rumbling noise comes from downstream. "+
	"To the west, the shore declines to a shallow bay.");
    set_tod_landname("the Emyn Muil");
    set_tod_landtype("river");
    set_tod_prependshort(1);
    set_long(tod_descs);
    add_item( ({ "sky", "sun", "moon", "star", "stars" }), tod_descs );

    set_watertype("river");
    set_watername("River Anduin");
    set_waterrefs( ({ "great river", "waters", "water", "river", "anduin",
	"river anduin", "anduin river" }) );
    set_downstreamdir( ({ "south", "southeast" }) );
    set_upstreamdir( ({ "north", "northeast" }) );
    set_currentstr( ({ 7, 7 }) ); /* rough */ 
    set_depth(305); /* 10 feet */
    set_rock_density(ROCKY);

    add_exit("river16w", "north");
    set_distance("north", 12);
    add_exit("river16e", "northeast");
    set_distance("northeast", 12);
    add_exit("river18", "south");
    add_exit("river18", "southeast");
    add_exit("river17e", "east");
    add_exit("bay17", "west");
    add_exit("riverbottom17w", "down");
    /* no shore rooms for now */


    add_item( ({ "great river", "waters", "water", "river anduin",
	"anduin river", "anduin", "river" }),
	BSN("The river here is wide and rocky. Its waters foam "+
	    "over protrusions of rock as they roll south."));
    add_item( ({ "protrusions", "protrusions of rock", "jagged rocks",
	"jagged teeth", "teeth", "rocky shoals", "shoals", "rock", "rocks" }),
	BSN("Rocks emerge from the river like jagged teeth, "+
	    "causing the waters to splash and froth."));
    add_item( ({ "emyn muil", "hill country", "country", "hills",
	"rugged country", "rugged hill country", "land", }),
	BSN("The Emyn Muil is a rugged land of high wind-scoured ridges "+
	    "crested with firs. It seems harsh and unwelcoming."));
    add_item( ({ "tree", "trees", "fir tree", "fir trees", "twisted fir",
	"twisted fir tree", "twisted firs", "twisted fir trees",
	"wind-writhen fir", "fir", "wind-writhen firs", "firs", }),
	BSN("Twisted, wind-writhen firs crown the ridges."));
    add_item( ({ "wind-scoured ridge", "high ridge", "ridge",
	"wind-scoured ridges", "high ridges", "ridges", }),
	BSN("The ridges rise in the distance,  beyond the low cliffs "+
	    "near the shores. They appear bleak and chill."));
    add_item( ({ "near shore", "near shores", "shore", "shores",
	"river bank", "river banks",
	"bank", "banks", }),
	BSN("The near shores are steep and rocky, with low cliffs "+
	    "just beyond."));
    add_item( ({ "eastern side", "eastern shore", "eastern bank",
	"east side", "east shore", "east bank", }),
	BSN("The stony slope, cloaked with thorns, rises sharply "+
	    "towards low cliffs and towering fingers of stone."));
    add_item( ({ "western side", "western shore", "western bank",
    	"west side", "west shore", "west bank", }),
	BSN("Beyond the bay, a steep bramble-covered shore climbs "+
	    "to meet weathered cliffs."));
    add_item( ({ "shoreline", "small bay", "shallow bay", "bay" }),
	BSN("The shoreline cuts west to form a small bay, "+
	    "whose waters appear calm and not very deep."));
    add_item( ({ "low cliff", "low cliffs", "weathered cliff",
	"weathered cliffs", "cliff", "cliffs", }),
	BSN("The stone of the cliffs is weathered and crumbling."));
    add_item( ({ "towering finger", "towering fingers", "finger", 
	"fingers", "slender finger", "slender fingers", "finger of stone", 
	"fingers of stone", "chimney", "chimneys" }),
	BSN("Slender fingers of stone rise like chimneys among the cliffs."));
    add_item( ({ "stone", "stones" }),
	BSN("The stone is dark gray and shows the effects of time "+
	    "and weather."));
    add_item( ({ "tangled mass", "tangled masses", "mass",
	"massess", "brake", "brakes", "thorn", "thorns", "bramble",
	"brambles", }),
	BSN("Tangled masses of thorns cling to the shores."));
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
	dir == "southeast" ||
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
