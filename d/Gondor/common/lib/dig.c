/*
 * /d/Gondor/common/lib/dig.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * inherit this to make "dig" take time, and paralyze mortal while
 * it's happening, just like "search"
 *
 * see /d/Gondor/common/doc/examples/room_dig.c for an example of its use.
 *
 * to use:
 * in create_gondor(), the following may be called (all are optional):
 *
 *    set_dig_pattern(string pat);
 *        where pat is a string suitable for use with parse_command().
 *	  for example: 
 *	      set_dig_pattern("[in] [the] [coarse] [brown] 'sand' / 'here'");
 *	  default is "'here'".
 *
 *    set_dig_time(int time);
 *    	  where time is the delay in seconds. default is 8.
 *
 *    set_dig_message(string msg);
 *	  where msg is the string to be inserted between "You start digging "
 *	  and " with your hands/shovel/...". for example,
 *	      set_dig_message("in the sand");
 *   	  default is "here".
 *
 *    set_dig_tools(mixed tool);
 *          where tool is either a string or an array of strings. each string
 *          is the name of an acceptable tool (which must be wielded) for
 *          digging.  default is to allow digging with any wielded object,
 *          or with bare hands.
 *    
 * The following are not optional:
 *
 * in init(), call:
 *	add_action(dig_here, "dig");
 *
 * in leave_inv(), call:
 *	stop_digging(ob);
 * (where ob is the departing object) before calling parent's leave_inv().
 *
 * provide code for the routine :
 *	public void
 *      dig_results(object digger)
 * that will called when the digging time has elapsed to describe the 
 * results of the digging, clone any objects, etc.  the argument
 * 'digger' is the person who did the digging.
 */

#pragma strict_types

#include <language.h>		/* for LANG_ADDART */
#include <composite.h>		/* for COMPOSITE_WORDS */
#include "/d/Gondor/defs.h"	/* always */

#define	DIG_TIME	8


/* prototypes */
public void		set_dig_pattern(string p);
public string		query_dig_pattern();
public void		set_dig_message(string m);
public string		query_dig_message();
public void		set_dig_tools(mixed t);
public string		*query_dig_tools();
public void		set_dig_time(int t);
public int		query_dig_time();
public int		dig_here(string arg);
public varargs int	stop_digging(mixed arg);
public void		dig_now(object digger);

static int	Dig_alarm,
		Dig_time = DIG_TIME;
static string	Dig_name,
		Dig_pattern = "'here'",
		Dig_message = "here",
		*Dig_tools = ({ });


/* the easy routines ... */
public void		set_dig_pattern(string p)	{ Dig_pattern = p;    }
public string		query_dig_pattern()		{ return Dig_pattern; }
public void		set_dig_message(string m)	{ Dig_message = m;    }
public string		query_dig_message()		{ return Dig_message; }
public void		set_dig_tools(mixed t)	   { Dig_tools = ARRAY(t);    }
public string		*query_dig_tools()		{ return Dig_tools;   }
public void		set_dig_time(int t)		{ Dig_time = t;       }
public int		query_dig_time()		{ return Dig_time;    }

/*
 * Function name:	dig_here
 * Description	:	parse attempts to dig, start digging
 *			if successful parse.
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 if we understand the arg, 0 if not
 *
 */
public int
dig_here(string arg)
{
    object	tp,
		used,
		*weaps,
		paralyze;
    string	usedstr;
    int		s;

    if (!strlen(arg))
    {
	NF0("Dig where?\n");
    }
    tp = TP;
    arg = LOW(arg);
    weaps = tp->query_weapon(-1);
    s = sizeof(weaps);
    if (!parse_command(arg, ({}), Dig_pattern))
    {
	if (parse_command(arg, ({}), Dig_pattern+" 'with' %s", usedstr))
	{
	    if (usedstr == "hands" ||
		usedstr == "hand")
	    {
		if (s)
		{
		    /* we firmly ignore "dig with left hand", etc */
		    NFN0("You cannot dig with your hands while "+
			"wielding the "+
			COMPOSITE_WORDS(weaps->short())+".");
		}
	    }
	    else if (!s ||
	             !parse_command(usedstr, weaps, "%o", used))
	    {
		NFN0("You are not wielding "+LANG_ADDART(usedstr)+".");
	    }
	}
	else
	{
	    NF0("Dig where?\n");
	}
    }
    if (objectp(used))
    {
	usedstr = used->short();
    }
    else if (s)
    {
	used = weaps[s-1];
	usedstr = used->short();
    }
    else
    {
	usedstr = "hands";
    }

    if ((s = sizeof(Dig_tools)))
    {
	if (!objectp(used))
	{
	    /* are they allowed to use hands? */
	    if (member_array("hands", Dig_tools) < 0)
	    {
		NFN0("You find it too difficult to dig "+Dig_message+
		    " with your hands.");
	    }
	}
	else
	{
	    /* they are using an object -- is it one we like? */
	    while (--s >= 0)
	    {
		if (used->id(Dig_tools[s]))
		{
		    break; /* while */
		}
	    }
	    if (s < 0)
	    {
		
		NFN0("You find it too difficult to dig "+Dig_message+
		    " with your "+usedstr+".");
	    }
	}
    }

    if (Dig_alarm)
    {
	WRITE(Dig_name+" is already digging here. You'll have to wait.");
	return 1;
    }

    WRITE("You begin digging "+Dig_message+" with your "+usedstr+".");
    SAY(" begins digging "+Dig_message+" with "+
	POSSESSIVE(tp)+" "+usedstr+".");
    Dig_alarm = set_alarm(itof(Dig_time), 0.0, &dig_now(tp));
    Dig_name = tp->query_name();
    FIX_EUID;
    paralyze = clone_object("/std/paralyze");
    paralyze->set_standard_paralyze("digging");
    paralyze->set_stop_fun("stop_digging");
    paralyze->set_remove_time(Dig_time);
    paralyze->move(tp, 1);
    return 1;
} /* dig_here */


/*
 * Function name:	stop_digging
 * Description	:	called when the paralyze time runs out, and 
 *			when the player does "stop digging".
 * Arguments	:	mixed arg -- if string, player did "stop"
 *				  -- if object, time ran out or
 *				      called from leave_inv().
 * Returns	:	0 -- always allow stop
 */
public int
stop_digging(mixed arg)
{
    if (!objectp(arg) ||
	(previous_object() == TO &&
	 living(arg) &&
	 arg->query_name() == Dig_name))
    {
	Dig_name = "";
	if (Dig_alarm)
	{
	    remove_alarm(Dig_alarm);
	    Dig_alarm = 0;
	}
    }
    return 0;
} /* stop_digging */
	

/*
 * Function name:	dig_now
 * Description	:	clear alarms, call routine to give results
 * Arguments	:	object digger -- the person digging
 */
public void
dig_now(object digger)
{
    Dig_name = "";
    Dig_alarm = 0;
    TO->dig_results(digger);
} /* dig_now */
