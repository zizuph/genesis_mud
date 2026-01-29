/*
 * /d/Gondor/std/water/inside_boat.c
 *
 * Copyright (C) 1997, 1998 by Nancy L. Mintz (Gnadnar)
 *
 * based on boat code of Elessar and of Fysix -- thanks, guys!
 *
 * thanks to Gilmanor for the code swiped from his find_thing.c!
 *
 * XXX:
 *	customize 'you row/leave/..." msgs
 *	weight of boat should affect fatigue
 */

#pragma strict_types

inherit "/d/Gondor/std/room";

#include <cmdparse.h>		/* for CMDPARSE_STD	*/
#include <composite.h>		/* for COMPOSITE_*	*/
#include <config.h>		/* for OWN_STATUE	*/
#include <files.h>              /* for IS_PLAYER_OBJECT */
#include <filter_funs.h>	/* for FILTER_LIVE	*/
#include <language.h>		/* for LANG_ADDART 	*/
#include <macros.h>		/* for QCTNAME		*/
#include <options.h>		/* for OPT_BRIEF	*/
#include <ss_types.h>		/* for SS_SWIM, etc	*/
#include <stdproperties.h>	/* for OBJ_I_*		*/
#include "/d/Gondor/defs.h"
#include "water_room.h"
#include "boat.h"

#ifndef ROOM_I_NO_ALLOW_STEED
#include "/d/Gondor/std/steed/steed.h"
#endif /* !ROOM_I_NO_ALLOW_STEED */

/* This definition is copied from OWN_STATUE, the room for linkdead people. */
#define PLAYER_S_LD_IN_ROOM "_player_s_ld_in_room"

static string  *Leave_cmd,		/* "leave", "disembark", ...	*/
	       *Row_cmd,		/* "row", "scull", "pole", ...	*/
	       *Oar_names,		/* names of objects that may	*/
					/* be used to row/scull/...	*/
		Inside_long;		/* long when inside boat	*/
static int	Min_boat_skill,		/* min skill to use boat	*/
		Min_depth,		/* need this much water to use 	*/
		Max_current;		/* strongest current in which	*/
					/* 	can be used		*/
static object	Boat;			/* external boat obj		*/


/* prototypes */
public void	create_inside_boat();
nomask void	create_gondor();
public void	set_boat(object boat);
public void	init();
public string	long_func();
public int	exa_view(string arg);
public int	do_leave(string arg);
public int	do_swim(string arg);
public int	check_oars_and_skill(string vb, string name);
public int	do_launch(string arg);
public int	do_row(string arg);
public void	leave_inv(object obj, object dest);
public void	capsize(object env);
public void	set_max_current(int max);
public void	set_leave_cmd(mixed cmd);
public void	set_row_cmd(mixed cmd);
public void	set_oar_names(mixed names);
public void	set_inside_long(string l);
public void	set_min_boat_skill(int sk);
public void	set_min_depth(int depth);
public string	*query_leave_cmd();
public string	*query_row_cmd();
public string	*query_oar_names();
public string	query_inside_long();
public int	query_min_boat_skill();
public int	query_min_depth();
public int	query_max_current();
public object	query_boat();
public varargs int	true();


/*
 * Function name:	create_inside_boat
 * Description	:	creator for inside_boat rooms
 * Configure your inside_boat here.
 */
public void
create_inside_boat()
{
} /* create_inside_boat */


/*
 * Function name:	create_gondor
 * Description	:	gondor room creator
 *
 * set up reasonable defaults before calling create_inside_boat()
 */
nomask void
create_gondor()
{
    if (!IS_CLONE)
    {
	return;
    }
    set_long(long_func);
    add_prop(ROOM_I_NO_CLEANUP, 1);
    add_prop(ROOM_I_HIDE, 50);
    add_prop(ROOM_M_NO_TELEPORT_TO, 1);
    add_prop(ROOM_I_NO_ALLOW_STEED, 1);
    set_noshow_obvious(1);
    Min_depth = MIN_SWIM_DEPTH;
    Max_current = 5;
    set_leave_cmd( ({ "leave", "disembark", "out" }) );
    set_row_cmd( ({ "row", "paddle" }) );
    set_oar_names( ({ "oars", "oar", "paddle" }) );
    set_min_boat_skill(MIN_BOAT_SKILL);

    create_inside_boat();

} /* create_gondor */



/*
 * Function name:	set_boat
 * Description	:	set the external boat obj, and be sure
 *			we have items for all the boat's
 *			names, and for "view"/"surroundings"
 * Arguments	:	object boat -- the external boat 
 */
public void
set_boat(object boat)
{
    string	myname = query_name(),
		*boatnames = boat->query_names(),
		artname;

    Boat = boat;

    /* be sure that our main name isn't ob_1743 */
    if (myname == OB_NAME(TO))
    {
	myname = boatnames[0];
	set_name(myname);
    }
    artname = LANG_ADDART(myname);

    if (!query_short())
    {
	set_short("inside "+artname);
    }

    if (!strlen(Inside_long))
    {
	if (boat->query_capacity() <= 2)
	{
	    Inside_long = "Inside "+artname+". It is not very big.\n";
	}
	else
	{
	    Inside_long = "Inside "+artname+".\n";
	}
    }

    /* if no items for "boat" etc, use default */
    if (!item_id(myname))
    {
	add_item(boatnames, Inside_long);
    }

} /* set_boat */


/* Function name:	init
 * Description	:	add player verbs
 */
public void
init()
{
    int s;

    ::init();

    s = sizeof(Leave_cmd);
    while (s-- > 0)
    {
    	add_action(do_leave, Leave_cmd[s]);
    }

    add_action(do_launch, "launch");
    s = sizeof(Row_cmd);
    while (s-- > 0)
    {
    	add_action(do_row, Row_cmd[s]);
    }

    add_action(do_swim, "swim");
    add_action(do_swim, "dive");
    add_action(do_swim, "wade");

    add_action(exa_view, "look");
    add_action(exa_view, "exa");
    add_action(exa_view, "examine");
} /* init */


/*
 * Function name:	long_func
 * Description	:	describe room, including whether is
 *				on water or land
 * Returns	:	string -- the description
 */
public string
long_func()
{
    object	env;
    mixed	ql;
    string	desc, vb = QVB;

    if (objectp(Boat) &&
	objectp(env = ENV(Boat)) &&
	env->query_prop(ROOM_I_IS))
    {
	if (TP->query_wiz_level() &&
	    (vb == "l" ||
	     vb == "look"))
	{
	    desc = file_name(env) + "\n" + Inside_long;
	}
	else
	{
	    desc = Inside_long;
	}
	ql = env->query_long();
	if (stringp(ql) ||
	    functionp(ql))
	{
	    return desc + check_call(ql);
	}
	if (env->query_prop(ROOM_I_TYPE) == ROOM_IN_WATER)
	{
	    return desc + 
		"The " + query_name() + " is on the " + 
		env->query_watername() + ".\n";
	}
	return desc + "The " + query_name() + " is on dry land.\n";
	
    }
    return Inside_long;
} /* long_func */


/*
 * Function name:	exa_view
 * Description	:	handle attempts to look at boat's env
 *			or items in the env
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	string -- the description
 *
 * special handling for "exa view" taken from d/Genesis/ship/deck.c
 *
 * XXX this is expensive, and is called every time player does
 * look/exa. is there a better way?
 */
public int
exa_view(string arg)
{
    object env, *inv, *live, *dead;
    string desc, live_desc, dead_desc, add_desc, save_exad;
    int i, s;

    if (!strlen(arg))
    {
	return 0;
    }
    arg = LOW(arg);
    desc = long(arg);
    if (strlen(desc))
    {
	write(desc);
	return 1;
    }

    if (!objectp(Boat) ||
	!objectp(env = environment(Boat)) ||
	!env->query_prop(ROOM_I_IS))
    {
	/* yikes */
	NF0("It seems as if the "+query_name()+
	    " is floating around in a void!\n");
    }
    save_exad = env->query_exa_arg();
    desc = env->long(arg);
    env->set_exa_arg(save_exad);
    if (strlen(desc))
    {
	write(desc);
	return 1;
    }
    if (arg != "view")
    {
	if (parse_command(arg, all_inventory(env), "%i", inv))
	{
	    inv = (object *)CMDPARSE_STD->visible_access(inv,
                "true", this_object(), 0, 0);
	    if (s = sizeof(inv))
	    {
		for (i = 0; i < s; ++i)
		{
		    write(inv[i]->long());
		}
		return 1;
	    }
	}
	return 0;
    }

    /* special handling for "exa view" */
    inv = all_inventory(env);
    live = FILTER_LIVE(inv);
    dead = filter(inv, "other_dead_than_this", TO, Boat);

    live_desc = ((live && sizeof(live)) ?
	capitalize(COMPOSITE_LIVE(live)) : 0);
    dead_desc = ((dead && sizeof(dead)) ?
	capitalize(COMPOSITE_DEAD(dead)) : 0);
    add_desc  = ((live_desc ? BSN(live_desc + ".") : "") +
                 (dead_desc ? BSN(dead_desc + ".") : ""));

    if (TP->query_option(OPT_BRIEF))
    {
        write(capitalize(env->short()) + ".\n" + add_desc);
	return 1;
    }
    write(env->long() + add_desc);
    env->set_exa_arg(save_exad);
    return 1;
} /* exa_view */


/*
 * Function name:	do_leave
 * Description	:	leave the boat if on land or if shallow water
 *			(they must use swim/dive to leave if deep water)
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 */
public int
do_leave(string arg)
{
    object	ob, env, tp = TP;
    string	name = query_name(), watertype;

    if (!objectp(Boat) ||
	!objectp(env = ENV(Boat)) ||
	!env->query_prop(ROOM_I_IS))
    {
	NFN0("It seems as if the "+name+" is floating around in a void!");
    }

    if (strlen(arg) &&
	!parse_command(LOW(arg), ({ Boat }), "[the] %o", ob))
    {
	NF0(capitalize(QVB)+" what?\n");
    }

    if (env->query_prop(ROOM_I_TYPE) != ROOM_IN_WATER)
    {
    	write("You leave the "+name+".\n");
	SAY(" leaves the "+name+".");
	tp->move_living("M", env);
	SAY(" arrives from the "+name+".");
    }
    else	/* is in water */
    {
	if (env->query_depth() > MAX_WADE_DEPTH)
	{
	    NF0("Wanna go for a swim or what?\n");
	}
	watertype = env->query_watertype();
	write("You wade from the "+name+" into the "+watertype+".\n");
	SAY(" wades from the "+name+" into the "+watertype+".");
	TP->add_prop(OBJ_I_WATER_MOVE, WATER_MOVE_WADE);
	tp->move_living("M", env);
	SAY(" wades from the "+name+" into the "+watertype+".");
    }
    return 1;
} /* do_leave */


/*
 * Function name:	do_swim
 * Description	:	swim/dive from boat
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 */
public int
do_swim(string arg)
{
    object	env, tp = TP;
    string	*waterrefs, watertype, name = query_name(), vb;
    int		depth, type;

    if (!objectp(Boat) ||
	!objectp(env = ENV(Boat)) ||
	!env->query_prop(ROOM_I_IS))
    {
	NFN0("It seems as if the "+name+" is floating around in a void!");
    }

    vb = QVB;
    if (env->query_prop(ROOM_I_TYPE) != ROOM_IN_WATER)
    {
	NF0("You cannot "+vb+" here.\n");
    }

    if (strlen(arg))
    {
	if (!sizeof(waterrefs = env->query_waterrefs()))
	{
	    waterrefs = ({ "water" });
	}
	if (!parse_command(LOW(arg), ({}),
		"[in] / [into] [the] %p", waterrefs))
	{
	    NF0(capitalize(vb)+" where?\n");
	}
    }

    if (vb != "wade")
    {
	if ((depth = env->query_depth()) < MIN_SWIM_DEPTH)
	{
	    write("The water is not deep enough to "+vb+".\n");
	    return 1;
	}
        if (tp->query_skill(SS_SWIM) < env->query_min_swim_skill(-1))
	{
	    WRITE("You have doubts about your swimming skills, and "+
		"decide to stay inside the "+name+".");
	    return 1;
	}
	vb = "dive";
	if (depth <= MAX_WADE_DEPTH)
	{
	    type = WATER_MOVE_WADE;	/* will stand up */
	}
	else
	{
	    type = WATER_MOVE_SWIM;
	}
    }
    else
    {
	if ((depth = env->query_depth()) > MAX_WADE_DEPTH)
	{
	    write("The water is too deep to wade.\n");
	    return 1;
	}
	type = WATER_MOVE_WADE;
    }
    tp->add_prop(OBJ_I_WATER_MOVE, type);
    if (!strlen(watertype = env->query_watertype()))
    {
	watertype = "water";
    }
    write("You "+vb+" into the "+watertype+".\n");
    SAY(" "+vb+"s into the "+watertype+".");
    set_dircmd("water");
    tp->move_living("M", env);
    SAY(" "+vb+"s into the "+watertype+" from the "+name+".");
    if (vb == "dive" &&
	depth <= MAX_WADE_DEPTH)
    {
	write("Your feet find firm bottom and you stand up in the "+
	    watertype+".\n");
	SAY(" stands up in the "+watertype+".");
    }
    return 1;
} /* do_swim */


/*
 * Function name:	check_oars_and_skill
 * Description	:	do the checks common to launch and row
 * Arguments	:	string vb -- player's verb
 *			string name -- name of boat
 * Returns	:	1 on success, 0 on failure
 */
public int
check_oars_and_skill(string vb, string name)
{
    object	*weps;
    string	*wepnames;
    int		i, n, s;


    if (TP->query_skill(SS_BOAT_HANDL) < Min_boat_skill)
    {
	NF0("You lack the skill to "+vb+" this "+name+".\n");
    }

    if (!(s = sizeof(weps = TP->query_weapon(-1))))
    {
	NF0("You cannot "+vb+" the "+name+" using your bare hands.\n");
    }

    n = sizeof(Oar_names);
    while (s-- > 0)
    {
	wepnames = weps[s]->query_names();
	for (i = 0; i < n; ++i)
	{
	    if (member_array(Oar_names[i], wepnames) >= 0)
	    {
		return 1;
	    }
	}
    }
    NFN0("You cannot "+vb+" the "+name+" using "+
	LANG_ADDART(weps[0]->short())+".");

} /* check_oars_and_skill */


/*
 * Function name:	do_launch
 * Description	:	handle attempts to launch boat
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 */
public int
do_launch(string arg)
{
    object	env,
		waterroom,
		ob;
    string	name = query_name(),
		tmpstr,
		waterpath,
		*waterrefs,
		watertype;
    int		*str;

    if (!strlen(arg))
    {
	NF0("Launch what?\n");
    }

    if (!objectp(Boat) ||
	!objectp(env = environment(Boat)) ||
    	!env->query_prop(ROOM_I_IS))
    {
	NFN0("It seems as if the "+name+" is floating around in a void!");
    }

    if (env->query_prop(ROOM_I_TYPE) == ROOM_IN_WATER &&
	env->query_depth() >= Min_depth)
    {
	NF0("The "+name+" already is in the water.\n");
    }

    arg = LOW(arg);
    /* launch boat, launch boat on river, launch boat east, etc */
    if (!parse_command(arg, ({ Boat }), "[the] %o", ob) &&
        !parse_command(arg, ({ Boat }),
	    "[the] %o 'in' / 'into' / 'on' / 'onto' [the] %s", ob, tmpstr) &&
        !parse_command(arg, ({ Boat }), "[the] %o %s", ob, tmpstr))
    {
	if (objectp(ob))
	{
		NF0("Launch the "+name+" where?\n");
	}
	NF0("Launch what?\n");
    }
    if (!strlen(waterpath = env->query_waterroom(tmpstr)))
    {
	NF0("Launch the "+name+" where?\n");
    }

    FIX_EUID;
    waterpath->short();
    waterroom = find_object(waterpath);
    if (!objectp(waterroom))
    {
	NF0("You can't seem to launch the "+name+" there.\n");
    }

    if (waterroom->query_depth() < Min_depth)
    {
	NF0("The water is too shallow to launch the "+name+".\n");
    }

    if (sizeof(str = waterroom->query_currentstr()) &&
	str[0] > Max_current)
    {
	NF0("The water is too rough to launch the "+name+".\n");
    }

    if (!check_oars_and_skill("launch", name))
    {
	return 0;	/* msg written in check_oars_and_skill() */
    }

    watertype = waterroom->query_watertype();
    WRITE("You launch the "+name+" into the "+watertype+".");
    SAY(" launches the "+name+" into the "+watertype+".");
    tell_room(env, "The "+name+" slides into the "+watertype+".\n");
    Boat->move(waterroom, 1);
    return 1;
} /* do_launch */


/*
 * Function name:	do_row
 * Description	:	move the boat somewhere
 * Arguments	:	string arg -- whatever the player typed
 *				(should be the direction to travel)
 * Returns	:	1 on success, 0 on failure
 */
public int
do_row(string arg)
{
    object	env, tp = TP, roomob, *passengers;
    string	tmpstr, nextroom, vb = QVB, name = query_name(), msg;
    int		fatigue, skill, *str, warn;

    if (!objectp(Boat) ||
	!objectp(env = environment(Boat)) ||
	!env->query_prop(ROOM_I_IS))
    {
	NFN0("It seems as if the "+name+" is floating around in a void!");
    }

    if (env->query_prop(ROOM_I_TYPE) != ROOM_IN_WATER)
    {
	NFN0("You cannot "+vb+" while the "+name+" is on dry land. "+
	    "Perhaps you should launch it first.");
    }

    if (!strlen(arg))
    {
	NF0(capitalize(vb)+" where?\n");
    }

    if (!check_oars_and_skill(vb, name))
    {
	return 0;	/* msg written in check_oars_and_skill() */
    }

    if (arg != "here")
    {
	if (strlen(tmpstr = env->expand_dir(arg)))
	{
	    arg = tmpstr;
	}
    }

    skill = tp->query_skill(SS_BOAT_HANDL);
    fatigue = env->swim_float_fatigue(skill, arg, WATER_MOVE_ROW, tp);
    Boat->set_pilot(tp);

    if (fatigue < 0 ||
        !strlen(nextroom = env->room_in_dir(arg)))
    {
	msg = env->query_no_exit_msg(arg);
	if (strlen(msg))         /* custom msg */
	{
    	    notify_fail(msg);
	}
	else
	{
	    notify_fail("You cannot seem to "+vb+" in that direction.\n");
	}
	return 0;
    }

    fatigue /= 3;
    DBG(tp, "rowing fatigue is "+fatigue+"\n");
    if (fatigue > tp->query_fatigue())
    {
	write("You try to row "+arg+", but are too exhausted.\n");
	SAY(" tries to row "+arg+", but is too exhausted.\n");
	return 1;
    }

    FIX_EUID;
    nextroom->short();
    roomob = find_object(nextroom);
    if (roomob->query_prop(ROOM_I_TYPE) == ROOM_IN_WATER)
    {
	/* if trying to row across or against the current and it
	 * is too strong for the player's swimming skill,
	 * there's a chance they fail.
	 */
	str = env->query_currentstr();
	if (arg != "downstream" &&
	    member_array(arg, env->query_downstreamdir()) < 0 &&
            env->current_too_strong(tp, skill, str[0], vb, arg))
	{
	    /* nope, current too strong for them. msg was 
	     * written in current_too_strong(), so just dock
	     * them the fatigue and bail out
	     */
	    tp->add_fatigue(-(fatigue));
	    return 1;
	}
    }

    tp->add_fatigue(-(fatigue));
    if (arg == "here")
    {
	add_prop(OBJ_I_SWAM_HERE, 1);
	write("You row in place.\n");
	SAY(" rows in place.");
    }
    else
    {
	if (env->check_efunc(arg))
	{
	    return 1;
	}
	tmpstr = Boat->short();
	write("You "+vb+" the "+name+" "+arg+".\n");
	SAY(" "+vb+"s the "+name+" "+arg+".");
	tell_room(env, "The "+tmpstr+" leaves "+arg+".\n");
	tell_room(TO, env->scenery_msgs(Boat, "row", arg));
	Boat->add_prop(OBJ_I_WATER_MOVE, WATER_MOVE_ROW);

	/*
	 * the boat may capsize and spill its passengers when it
	 * enters the new room.  if this happens, they will enter the
	 * room immediately after the boat capsizes and *before* this
	 * call to move(nextroom,1) returns, which means they already will
	 * have seen "a capsized rowboat" in the new room's inventory.
	 * therefore, we have to remember the passengers so we don't
	 * show them the "arrives" msg
	 */
	passengers = FILTER_LIVE(all_inventory(TO));
	Boat->move(nextroom, 1);
	if (!objectp(Boat))
	{
	    /* it broke apart on rocks, most likely */
	    return 1;
	}
	Boat->remove_prop(OBJ_I_WATER_MOVE);
	env = ENV(Boat);
	if (env->query_prop(ROOM_I_TYPE) == ROOM_IN_WATER)
	{
	    tell_room(env, CAP(LANG_ADDART(tmpstr))+" arrives.\n",
		passengers);
	    if (!Boat->query_capsized() &&
		env->query_depth() < Min_depth)
	    {
		tell_room(TO, 
		    "The "+tmpstr+" runs aground in "+
		    "the shallow water.\n");
	    }
	}
	else
	{
	    tell_room(TO, "The "+name+" comes to rest on the shore.\n");
	    tell_room(env, CAP(LANG_ADDART(tmpstr))+
		(Boat->query_capsized ? " glides" : " washes")+
		" out of the water.\n", passengers);
	}
    }
    if (!Boat->query_capsized())
    {
	env->warn_boat(tp, skill, Max_current, TO);
    }
    return 1;
} /* do_row */


/*
 * Function name:	leave_inv
 * Description	:	linkdead players come into the room where this boat is.
 * Arguments	:	object obj -- the leaving object
 *			object dest -- where it's going
 */
public void
leave_inv(object obj, object dest)
{
    ::leave_inv(obj, dest);

    if (IS_PLAYER_OBJECT(obj) &&
	objectp(dest) &&
	objectp(environment(Boat)) &&
	file_name(dest) == OWN_STATUE)
    {
        obj->add_prop(PLAYER_S_LD_IN_ROOM, file_name(environment(Boat)));
    }
} /* leave_inv */


/*
 * Function name:	capsize
 * Description	:	the boat turns over -- spill contents
 * Arguments	:	object env -- where to spill to
 */
public void
capsize(object env)
{
    object	ob, *inv, *lv, *dd;
    string	name, vb, where;
    int		s;

    if (!objectp(env) ||
	!env->query_prop(ROOM_I_IS))
    {
	ob = previous_object();
	ERR_LOG("capsize() called from previous object " +
	    (objectp(ob) ? file_name(ob) : "NULL") +
	    " with bad env " +
	    (objectp(env) ? file_name(env) : "NULL") + "\n");
	return;
    }

    if (env->query_prop(ROOM_I_TYPE) == ROOM_IN_WATER)
    {
	vb = "capsizes";
	where = "into the water.\n";
    }
    else
    {
	vb = "overturns";
	where = "onto the ground.\n";
    }
    name = query_name();
    tell_room(env, "The "+name+" "+vb+"!\n");

    if (!sizeof(inv = all_inventory(TO)))
    {
	return;
    }
    lv = FILTER_LIVE(inv);
    dd = FILTER_SHOWN(inv - lv);
    if ((s = sizeof(lv)))
    {
	tell_room(TO,
	    "The "+name+" "+vb+", tumbling you "+where);
	tell_room(env,
	    capitalize(COMPOSITE_LIVE(lv))+
		(s > 1 ? " tumble" : " tumbles")+
		" out of the "+name+".\n");
	if (env->query_depth() > MAX_WADE_DEPTH)
	{
	     lv->add_prop(OBJ_I_WATER_MOVE, WATER_MOVE_FLOAT);
	}
	lv->move_living("M", env);
    }
    if ((s = sizeof(dd)))
    {
	tell_room(env,
	    capitalize(COMPOSITE_LIVE(dd))+
		((s > 1 || dd[0]->num_heap() > 1) ? " fall" : " falls")+
		" out of the "+name+".\n");
	dd->move(env, 1);
    }
} /* capsize */


/* 
 * Function name:	set_max_current
 * Description	:	set the max current str in which the boat can
 *			be used (subject to range checks)
 * Arguments	:	int max -- the max current str
 */
public void
set_max_current(int max)
{
    Max_current = CHECK_RANGE(max, MIN_CURRENT, (MAX_CURRENT - 1));
} /* set_max_current */


/* generic set-and-query stuff */
public void	set_leave_cmd(mixed cmd)  { Leave_cmd = ARRAY(cmd);    }
public void	set_row_cmd(mixed cmd)    { Row_cmd = ARRAY(cmd);      }
public void	set_oar_names(mixed names){Oar_names = ARRAY(names);   }
public void	set_inside_long(string l)   { Inside_long = l;		   }
public void	set_min_boat_skill(int sk)  { Min_boat_skill = sk;	   }
public void	set_min_depth(int depth)    { Min_depth = depth;	   }
public string  *query_leave_cmd()	    { return Leave_cmd;		   }
public string  *query_row_cmd()		    { return Row_cmd;		   }
public string  *query_oar_names() 	    { return Oar_names;	   }
public string	query_inside_long() 	    { return Inside_long;	   }
public int	query_min_boat_skill() 	    { return Min_boat_skill; 	   }
public int	query_min_depth() 	    { return Min_depth; 	   }
public int	query_max_current() 	    { return Max_current; 	   }
public object	query_boat()		    { return Boat;		   }
public varargs int	true() 		    { return 1; }
