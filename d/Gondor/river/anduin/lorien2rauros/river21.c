/*
 * /d/Gondor/river/anduin/lorien2rauros/river21.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * in the teeth of sarn gebir. looks like you die.
 *
 * 'Boats of the Elves would not sink, maybe,' he said, 'but that
 *  does not say that we should come through Sarn Gebir alive.
 *  None have ever done so yet.'
 *
 * well, they *might* survive -- if they're quick with a gem or wand
 * of teleportation.  players hit rocks on entering and again at alarm
 * intervals of 5 seconds.  each impact with rock does from max_hp/4 to
 * max_hp/2 damage, so at best they have 15 seconds and at worst 5 seconds
 * to teleport out before they drown.
 */

#pragma strict_types

inherit "/d/Gondor/river/anduin/anduin_onwater";
inherit "/d/Gondor/common/lib/tod_descs";

#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/std/water/onwater.h"
#include <adverbs.h>
#include "../anduin.h"

#define	ALARM_INTERVAL	5.0

/* prototypes */
public void	create_anduin_onwater();
public void	enter_inv(object ob, object from);
public void	init();
public int	do_listen(string arg);
public int	exa_noise_icky(string arg);
public int	no_escape();
public int	check_hit_rock(object ob);
public int	check_capsize(object ob);
public int	current_too_strong(object tp, int sk, int str, string verb,
							string	dir);


/*
 * Function name:	create_anduin_onwater
 * Description	:	set up the room
 */
public void
create_anduin_onwater()
{
    add_prop(OBJ_S_WIZINFO,
	BSN("In the teeth of sarn gebir, 338 miles downstream from "+
	    "the silverlode. None come through these waters alive."));
    set_short("in the rapids of Sarn Gebir");

    set_tod_long(
	"The waters churn violently as they crash against "+
	"rocks that jut from the river like great jagged teeth. "+
	"Foam sprays high into the air, and the noise is deafening.");

    set_tod_landname("the Emyn Muil");
    set_tod_landtype("river");
    set_tod_prependshort(1);

    /* for this room, omit time-of-day details in long desc.
     * it seems silly to append to these descs a calm observation
     * about the twinkling stars and the moon's uptilted horns.
     * also, mortals are in grave danger so the less spam the better.
     * continue to use tod_descs for tod items, tho.
     */
    set_long(BSN(CAP(short())+". "+query_tod_long()));
    add_item( ({ "sky", "sun", "moon", "star", "stars" }), tod_descs );

    set_watertype("river");
    set_watername("River Anduin");
    set_waterrefs( ({ "great river", "waters", "water", "river", "anduin",
	"river anduin", "anduin river" }) );
    set_downstreamdir("south");
    set_upstreamdir( ({ "northeast", "north", "northwest" }) );
    set_depth(305);	/* 10 feet */
    set_currentstr(MAX_CURRENT);
    set_rock_density(MAX_ROCKS);

    add_exit("river21", "west", no_escape, 0, 1);
    add_exit("river21", "east", no_escape, 0, 1);
    add_exit("river21", "here", no_escape, 0, 1);
    add_exit("river18e", "northeast", no_escape, 0, 1);
    add_exit("river18e", "north", no_escape, 0, 1);
    add_exit("river18w", "northwest", no_escape, 0, 1);
    add_exit("river22", "south", no_escape, 0, 1);
    add_exit("river22", "southeast", no_escape, 0, 1);
    add_exit("river22", "southwest", no_escape, 0, 1);
    add_exit("riverbottom21", "down", no_escape, 0, 1);
    /* no shore rooms */

    add_item( ({ "sarn gebir", "rapids" }), long);
    add_item( ({ "great river", "waters", "water", "river anduin",
	"anduin river", "anduin", "river" }),
	BSN("The waters of the Anduin pound against the stony "+
	    "teeth of Sarn Gebir, filling the air with foam and mist."));
    add_item( ({ "foam", "mist", "air" }),
	BSN("Mist from the churning waters hangs in the air above "+
	    "the rapids."));
    add_item( ({ "great jagged teeth", "jagged teeth", "teeth",
	"stony teeth", "fang", "fangs", "jagged rock", "jagged rocks",
	"rock", "rocks" }),
	BSN("The rocks jut up like fangs, lashing the waters "+
	    "to foam."));
    add_item( ({ "eastern side", "eastern shore", "eastern bank", 
    	"east side", "east shore", "east bank", 
    	"western side", "western shore", "western bank",
    	"west side", "west shore", "west bank",
    	"shore", "shores", "river bank", "river banks",
	"bank", "banks", }),
	BSN("The shores rise steeply above the rapids, in "+
	    "a near-vertical expanse of gray stone."));
    add_item( ({ "near-vertical expanse", "expanse", 
	"steep slope", "steep slopes", "slope", "slopes" }),
	BSN("Steep slopes of gray stone close in around Sarn Gebir."));
    add_item( ({ "gray stone", "stone" }),
	BSN("The gray stone seems to merge with the mist of the river."));
    add_item( ({ "emyn muil" }),
	BSN("The steep slopes, shrouded in mist, "+
	    "are all that can be seen of the Emyn Muil."));
} /* create_anduin_onwater */


/*
 * Function name:	enter_inv
 * Description	:	mask parent to ensure that livings hit rocks
 * Arguments	:	object ob -- the entering object
 *			object from -- its source
 */
public void
enter_inv(object ob, object from)
{

    int		set_prop;

    if (living(ob) &&
	!ob->query_ghost() &&
        !ob->query_prop(OBJ_I_NO_WASH))
    {
	set_prop = 1;
	ob->add_prop(OBJ_I_NO_WASH, 1);
    }

    ::enter_inv(ob, from);

    if (!objectp(ob))
    {
	return;
    }

    if (set_prop)
    {
	/* living MUST hit rock.
	 * check_hit_rock will set any alarms.
	 */
	ob->remove_prop(OBJ_I_NO_WASH);
	if (ENV(ob) == TO)
	{
	    check_hit_rock(ob);
	}
    }
    /* else alarm will have been set in parent */
} /* enter_inv */



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
	WRITE("The noise of the water crashing onto the rocks "+
	    "all but deafens you.");
	return 1;
    }

    arg = LOW(arg);
    if (arg == "." ||
        strlen(FULL_ADVERB(arg)))
    {
         return 0;	/* fall thru to soul */
    }

    if (parse_command(arg, ({}),
		      "[to] [the] [deafening] %s", tmpstr) &&
        (tmpstr == "rumble" ||
	 tmpstr == "rumbling" ||
	 tmpstr == "river" ||
         tmpstr == "water" ||
         tmpstr == "noise" ||
         tmpstr == "sound" ||
         tmpstr == "rapids" ||
         tmpstr == "sarn gebir"))
    {
	WRITE("The noise of the water crashing onto the rocks "+
	    "all but deafens you.");
    }
    else if (parse_command(arg, ({}),
	     "[to] [the] [loud] [bass] [rumble] / [rumbling] %s", tmpstr) &&
	     (tmpstr == "" ||
	      tmpstr == "noise" ||
	      tmpstr == "sound" ||
	      tmpstr == "rapids" ||
	      tmpstr == "sarn gebir"))
    {
	WRITE("The noise of the water crashing onto the rocks "+
	    "all but deafens you.");
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
	if ((parse_command(arg, ({}),
		      "[at] [the] [deafening] %s", tmpstr) &&
             (tmpstr == "rumble" ||
	      tmpstr == "rumbling" ||
	      tmpstr == "noise" ||
              tmpstr == "sound")) ||
	    (parse_command(arg, ({}),
	     "[at] [the] [loud] [bass] [rumble] / [rumbling] %s", tmpstr) &&
	     (tmpstr == "" ||
	      tmpstr == "noise" ||
	      tmpstr == "sound")))
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
 * Function name:	no_escape
 * Description	:	block escape
 * Returns	:	1 -- no exit
 */
public int
no_escape()
{
    object	env = ENV(TP),
		boat;
    string	response,
		vb = QVB;

    if (env == TO)
    {
	/* swimmer */
	if (vb == "down" ||
	    vb == "dive")
	{
	    response = "You try to dive";
	}
	else
	{
	    response = "You try to swim "+query_move_direction();
	}
	write(BSN(response+", but the torrential currents are far "+
	    "too strong. You are helpless to control your movement."));
    }
    else if (objectp(boat = env->query_boat()))
    {
	/* else it's a boat, so (i believe) this is not reached.
	 * all boats capsize on entry, and current is too rough
	 * for players to flip them upright again. however, it
	 * doesn't hurt to check.
	 */
	WRITE("The torrential currents are far "+
	    "too strong. You are helpless to control the "+
	    boat->short()+".");
	/* this boat shouldn't be here ... try again to capsize it */
	check_hit_rock(boat);
    }
    else	/* "cannot happen" */
    {
	write("The current is too strong.\n");
    }
    return 1;
} /* no_escape */


/*
 * Function name:	check_hit_rock
 * Description	:	mask parent --  entering ob hits rocks
 * Arguments	:	object ob -- the player or boat
 * Returns	:	1 (always)
 */
public int
check_hit_rock(object ob)
{
    int dmg;

    if (!ob &&
	ENV(TP) == TO)
    {
	ob = TP;
    }

    if (living(ob))
    {
	dmg = ob->query_max_hp()/4;
	dmg += random(dmg);
	write("Helpless in the torrential currents, "
	    + "you slam headfirst into a rock.\n");
	SAY(" slams headfirst into a rock.");
	ob->reduce_hit_point(dmg);
	if (ob->query_hp() <= 0)
	{
	    write(BSN("You are too stunned by the blow to keep "+
		"swimming. You drown in the rapids of Sarn Gebir."));
	    SAY(" appears stunned by the blow. "+
	    CAP(ob->query_pronoun())+
			" sinks beneath the water and drowns.");
	    INFO_LOG(ob->query_real_name()+" ("+
		ob->query_average_stat()+
		") hit a rock and drowned.\n");
	    ob->do_die(TO);
	}
	else
	{
	    /* they didn't die -- hit 'em again */
	    ob->add_prop(OBJ_I_WATER_ALARM,
		set_alarm(ALARM_INTERVAL, 0.0, &check_hit_rock(ob)));
	}
    }
    else if (!IS_ELVEN_BOAT(ob))
    {
	/* enter_inv() will set float-away alarm on the splinters */
	ob->break_apart("The rocks of Sarn Gebir smash the "+
	    ob->query_name()+" to splinters.\n");
    }
    else if (!ob->query_capsized())
    {
	ob->set_capsized(1);
    }
    return 1;
} /* check_hit_rock */


/*
 * Function name:	check_capsize
 * Description	:	mask parent ... boats always capsize here
 * Arguments	:	object ob -- the boat
 * Returns	:	1 (always)
 */
public int
check_capsize(object ob)
{
    return 1;
} /* check_capsize */


/*
 * Function name:	current_too_strong
 * Description	:	mask parent ... exit efun has already done this
 * Arguments	:	object tp -- the player
 *			int sk -- her/his swim skill
 *			int str -- the current strength
 *			string verb -- "swim", "float", "dive"
 *			string dir -- direction of movement
 * Returns	:	0 (always) -- movement succeeds
 */
public int
current_too_strong(object tp, int sk, int str, string verb, string dir)
{
    return 0;
} /* current_too_strong */
