/*
 * /d/Gondor/river/anduin/lorien2rauros/river16e.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * day 7 campsite, 325 miles downstream of silverlode
 * XXX "listen" code is makeshift -- replace with the real
 *      stuff from gilmanor
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
	BSN("day 7 campsite, 325 miles downstream from silverlode"));
    set_short("on the east side of the River Anduin");

    /* use tod_descs to append time-of-day descriptions to long
     * and to handle sky items
     */
    set_tod_long("The Great River passes swiftly through "+
	"rugged hill country, tumbling over rocks as it flows south. "+
	"From somewhere downstream, there comes a low rumbling noise.");
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
    set_rock_density(ROCKY - 1);

    add_exit("river15e", "north");
    set_distance("north", 25);
    add_exit("river15w", "northwest");
    set_distance("northwest", 25);
    add_exit("river17e", "south");
    set_distance("south", 12);
    add_exit("river17w", "southwest");
    set_distance("southwest", 12);
    add_exit("river16w", "west");
    add_exit("riverbottom16e", "down");
    /* no shore rooms for now */

    add_item( ({ "great river", "waters", "water", "river anduin",
	"anduin river", "anduin", "river" }),
	BSN("The waters foam and froth against the rocks."));
    add_item( ({ "emyn muil", "hill country", "country", "hills",
	"rugged country", "rugged hill country", "land", }),
	BSN("Beyond the steep, thorny shores stand low crumbling "+
	    "cliffs and chimneys of gray weathered stone dark with "+
	    "ivy."));
    add_item( ({ "shore", "shores", "river bank", "river banks",
	"bank", "banks", "eastern shore", "eastern bank",
	"western shore", "western bank", "east shore",
	"east bank", "west shore", "west bank", }),
	BSN("The stony shores, blanketed with bramble, "+
	    "rise steeply away from the river."));
    add_item( ({ "stone", "stones" }),
	BSN("The steep slope of the shore is of the same gray stone "+
	    "as the more distant chimneys."));
    add_item( ({ "jagged rocks", "rocky shoals", "shoals", "rock", "rocks" }),
	BSN("Jagged rocks, extending just above the water surface, "+
	    "cause the river to foam as it flows past."));
    add_item( ({ "thicket", "thickets", "brake", "brakes",
	"thorn", "thorns", "bramble", "brambles", }),
	BSN("Tangled brambles cloak both shores."));
    add_item( ({ "low cliff", "low cliffs", "crumbling cliff",
	"crumbling cliffs", "cliff", "cliffs", }),
	BSN("The cliffs are crumbled with age and weather."));
    add_item( ({ "ivy", "slender chimney", "slender chimneys", 
    	"chimney", "chimneys", }),
	BSN("The slender chimneys are obscured by ivy."));
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

    if (parse_command(arg, ({}), "[to] [the] [low] "+
		"[rumble] / [rumbling] %s", tmpstr) &&
        (tmpstr == "downstream" ||
         tmpstr == "" ||
         tmpstr == "sound" ||
         tmpstr == "noise" ||
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
		"[at] [the] [low] [rumble] / [rumbling] %s", tmpstr) &&
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
 * Description	:	mask parent to give warning msgs
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
	desc = BSN("As you travel downstream, the river "+
	           "becomes alarmingly violent.");
    }
    else
    {
	desc = "";
    }
    return desc;
} /* scenery_msgs */
