/*
 * /d/Gondor/river/anduin/lorien2rauros/river19.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * just above sarn gebir. head upstream or die!
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
public int	no_dive();


/*
 * Function name:	create_anduin_onwater
 * Description	:	set up the room
 */
public void
create_anduin_onwater()
{
    add_prop(OBJ_S_WIZINFO,
	BSN("just above sarn gebir, about 337.5 miles downstream from "+
	    "the silverlode."));
    set_short("on the River Anduin");

    set_tod_long(
	"Great jagged rocks lash the river to foam as, "+
	"with a thunderous roar, it races towards the dreaded "+
	"rapids of Sarn Gebir.  There is little time left to escape!");

    set_tod_landname("the Emyn Muil");
    set_tod_landtype("river");
    set_tod_prependshort(1);

    /* for these rooms approaching sarn gebir, omit time-of-day details
     * in long desc.  it seems silly to append to these descs a calm
     * observation about the twinkling stars and the moon's uptilted horns.
     * continue to use tod_descs for tod items, tho.
     */
    set_long(BSN(CAP(short())+". "+query_tod_long()));
    add_item( ({ "sky", "sun", "moon", "star", "stars" }), tod_descs );


    set_watertype("river");
    set_watername("River Anduin");
    set_waterrefs( ({ "great river", "waters", "water", "river", "anduin",
	"river anduin", "anduin river" }) );
    set_downstreamdir( ({ "south" }) );
    set_upstreamdir( ({ "north", "northwest" }) );
    set_currentstr( ({ 8 }) );	/* wild */
    set_depth(305); /* 10 feet */
    set_rock_density(ROCKY+1);

    add_exit("river18", "north");
    add_exit("river20", "south");
    add_exit("riverbottom19", "down", no_dive);	/* never succeeds */
    /* no shore rooms */

    add_item( ({ "great river", "waters", "water", "river anduin",
	"foaming waters", "wildly foaming waters", "foaming water",
	"wildly foaming water", "anduin river", "anduin", "river" }),
	BSN("The Great River boils over the jagged rocks as it "+
	    "plunges south towards Sarn Gebir."));
    add_item( ({ "jagged rocks", "sharply pointed rocks", "pointed rocks",
	"jagged fangs", "fangs", "fangs of stone", "jagged fangs of stone", 
	"rocky shoals", "shoals", "rock", "rocks" }),
	BSN("Jagged fangs of stone slash the river as it races south."));
    add_item( ({ "eastern side", "eastern shore", "eastern bank", 
    	"east side", "east shore", "east bank", 
    	"western side", "western shore", "western bank",
    	"west side", "west shore", "west bank",
    	"shore", "shores", "river bank", "river banks",
	"bank", "banks", }),
	BSN("Steep rock faces rise on each side of the river."));
    add_item( ({ "barren slope", "barren slopes", "slope", "slopes",
	"rocky slope", "rocky slopes", "rock face", "rock faces",
	"face", "faces" }),
	BSN("Barren slopes of gray stone rise almost vertically "+
	    "from the water."));
    add_item( ({ "stone", "gray stone" }),
	BSN("The stone is steep and bare of life."));
    add_item( ({ "emyn muil" }),
	BSN("The sheer rocky slopes lining both sides of the river "+
	    "are all that can be seen of the Emyn Muil."));
    add_item( ({ "deadly rapids", "deadly rapids of sarn gebir",
	"rapids", "rapids of sarn gebir", "sarn gebir" }),
	BSN("Just a short way downstream, the waters boil through "+
	    "the rapids of Sarn Gebir."));
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
    if (!strlen(arg))
    {
	WRITE("You hear the thunder of the deadly rapids "+
	    "of Sarn Gebir very close at hand!");
	return 1;
    }

    arg = LOW(arg);
    if (arg == "." ||
        strlen(FULL_ADVERB(arg)))
    {
         return 0;	/* fall thru to soul */
    }

    if (parse_command(arg, ({}),
	"[to] [the] [thunderous] 'roar' / 'thunder' / 'sound' / "+
	"'noise' / 'rapids' / 'sarn' [gebir]"))
    {
	WRITE("You hear the thunder of the deadly rapids "+
	    "of Sarn Gebir very close at hand!");
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
    if (strlen(arg))
    {
	if (parse_command(arg, ({}),
	    "[at] [the] [thunderous] 'roar' / 'thunder' / 'sound' / "+
	    "'noise'"))
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
 * Function name:	no_dive
 * Description	:	block attempts to dive
 * Returns	:	1 -- exit always fails
 */
public int
no_dive()
{
    WRITE("The water is much too turbulent -- you are tossed "+
	"back to the surface.");
    return 1;
} /* no_dive */
