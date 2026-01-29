/*
 * /d/Gondor/river/anduin/lorien2rauros/river15w.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * north edge of emyn muil, ~45 miles downstream of day 6 campsite
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
	BSN("north edge of emyn muil, ~45 miles downstream of day "+
	    "6 campsite, about 300 miles downstream from silverlode."));
    set_short("on the west side of the River Anduin");

    /* use tod_descs to append time-of-day descriptions to long
     * and to handle sky items
     */
    set_tod_long("The waters, flowing south past steep slopes on both "+
	"shores, swirl across rocky shoals. "+
	"From downstream, just at the edge of hearing, there comes "+
	"a faint rumbling noise.");
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
    set_currentstr( ({ 6, 6 }) ); /* rapid */ 
    set_depth(610); /* 20 feet */
    set_rock_density(SCATTERED_ROCKS + 2);

    add_exit("river14w", "north");
    set_distance("north", 25);
    add_exit("river14e", "northeast");
    set_distance("northeast", 25);
    add_exit("river16w", "south");
    set_distance("south", 25);
    add_exit("river16e", "southeast");
    set_distance("southeast", 25);
    add_exit("river15e", "east");
    add_exit("riverbottom15w", "down");
    /* no shore rooms for now */

    add_item( ({ "great river", "waters", "water", "river anduin",
	"anduin river", "anduin", "river" }),
	BSN("The river flows swiftly over rocky shoals."));
    add_item( ({ "land", "rocky land", "shore", "shores", "river bank",
	"river banks", "bank", "banks", "eastern shore",
	"eastern bank", "western shore", "western bank",
	"east shore", "east bank", "west shore", "west bank", }),
	BSN("On both shores, steep slopes are tangled with "+
	    "brambles and creepers."));
    add_item( ({ "stone", "stones", "slope", "slopes" }),
	BSN("The stony slopes support nothing but brambles and thorns."));
    add_item( ({ "rocks", "rock", "rocky shoals", "shoals", }),
	BSN("Long rocky shoals churn the river as it flows past."));
    add_item( ({ "thicket", "thickets", "thorn", "thorns", "bramble",
	"vine", "vines", "brambles", "creeper", "creepers", }),
	BSN("Both shores are buried in brambles and creeping vines."));
     add_item( ({ "hill", "hills", "emyn muil", }),
	BSN("The high ridges of the Emyn Muil are bare and "+
	    "scoured by wind."));
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
	WRITE("Somewhere to the south are rumoured to be the deadly rapids "+
	    "of Sarn Gebir, through which none have ever passed alive. "+
	    "Perhaps it is the noise of the rapids you hear.");
	return 1;
    }

    arg = LOW(arg);
    if (arg == "." ||
        strlen(FULL_ADVERB(arg)))
    {
         return 0;	/* fall thru to soul */
    }

    if (parse_command(arg, ({}), "[to] [the] [faint] "+
		"[rumble] / [rumbling] %s", tmpstr) &&
        (tmpstr == "downstream" ||
         tmpstr == "" ||
         tmpstr == "noise" ||
         tmpstr == "sound" ||
         tmpstr == "rapids" ||
         tmpstr == "sarn gebir"))
    {
	WRITE("Somewhere to the south are rumoured to be the deadly rapids "+
	    "of Sarn Gebir, through which none have ever passed alive. "+
	    "Perhaps it is the noise of the rapids you hear.");
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
		"[at] [the] [faint] [rumble] / [rumbling] %s", tmpstr) &&
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
 * Description	:	mask parent to give a "the banks soften" msg
 *			if people or boats are going downstream.
 * Arguments	:	object ob -- who/what is moving
 *			string vb -- "swim", "wade", "row", "dive", "wash"
 *			string dir -- the direction of movement
 */
public string
scenery_msgs(object ob, string vb, string dir)
{
    string desc;

    if (dir == "north" ||
	dir == "northeast" ||
	dir == "upstream")
    {
	desc = BSN("As you travel upstream, "+
	           "the stony banks soften into rolling downs.");
    }
    else if (dir == "south" ||
	     dir == "southeast" ||
	     dir == "downstream")
    {
	desc = BSN("As you travel downstream, the current grows quite "+
	           "strong and jagged rocks loom large.");
    }
    else
    {
	desc = "";
    }
    return desc;
} /* scenery_msgs */
