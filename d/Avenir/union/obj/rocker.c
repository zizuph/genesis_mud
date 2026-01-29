// file name: rocker.c
// creator(s): Lilith, March 2004
/*
 * Revisions:
 *   Lucius, Jun 2016: Added sub-object for capturing linkdeath.
 *   Lucius, Jun 2017: Re-Code.
 */
#pragma strict_types
inherit "/std/object";

#include "../defs.h"

#include <macros.h>
#include <cmdparse.h>
#include <composite.h>
#include <stdproperties.h>

private object sitting, in_lap;

public string sitting_on_cushion(void);


public mixed
get_me(void)
{
    if (sitting)
	return "It is in use.\n";

    return 0;
}

public string
my_long(void)
{
    string str = "This is a rocking chair, made of bent wood. It looks "+
	"light weight and more than a little rickety.\n";

    return str + sitting_on_cushion();
}

private string
get_name(object who, int lap)
{
    string str = (lap ? " and " : "");

    if (!objectp(who))
	return "";
    else if (who == TP)
	str += "you" + (lap ? "rself" : "");
    else
	str += who->query_the_name(TP);

    return str;
}

public string
real_short(void)	{ return "rocking chair"; }

public string
my_short(void)
{
    if (!sitting)
	return real_short();

    return real_short() +" with "+
	get_name(sitting, 0) + get_name(in_lap, 1) +
	" sitting in it";
}

public void
create_object(void)
{
    reset_euid();
    set_short(my_short);
    set_long(my_long);
    set_name("chair");
    add_name(({"rocker"}));
    set_adj("rocking"); 
    add_prop(OBJ_I_VALUE, 1540);
    add_prop(OBJ_M_NO_GET, get_me);
}

/*
 * Function name: sitting_on_cushion
 * Description  : Combine those sitting into a nicely formatted string.
 * Returns      : (string) the formatted text.
 */
public string
sitting_on_cushion(void)
{
    string seated;

    if (!objectp(sitting))
	return "";

    if (sitting == TP)
    {
	seated = "You are seated on the "+ real_short();
    }
    else
    {
	seated = sitting->query_The_name(TP) +
	    " is seated on the "+ real_short();
    }

    if (objectp(in_lap))
    {
	if (sitting == TP)
	{
	    seated += " with "+ in_lap->query_The_name(TP) +
		" sitting on your lap";
	}
	else if (in_lap == TP)
	{
	    seated += " with you in "+
		sitting->query_the_possessive_name(TP) + " lap";
	}
	else
	{
	    seated += " with "+ in_lap->query_The_name(TP) +
		" sitting on " + sitting->query_the_posessive_name(TP) +
		" lap";
	}
    }

    return seated + ".\n";
}

private void
cleanup_rocker(object who)
{
    object *obs = all_inventory(who);
    foreach(object ob: filter(obs, &->id("__rocker_obj")))
	set_alarm(0.0, 0.0, &ob->remove_object());
}

/*
 * Function name: do_rise
 * Description  : command to rise
 * Argument     : string str - the argument to the command
 * Returns      : (int) 1/0 - I handled this / SEP
 */
public int
do_rise(string str)
{
    object obj;

    if (strlen(str) && str != "up")
    {
	notify_fail(capitalize(query_verb()) + " what? Up perhaps?\n");
	return 0;
    }

    if (in_lap == TP)
    {
	TP->catch_msg("You get up from " + QTPNAME(sitting) + " lap.\n");
	tell_room(environment(), QCTNAME(TP) + " gets up from " +
	    QTPNAME(sitting) + " lap.\n", ({ TP, sitting }));
	sitting->catch_msg(QCTNAME(TP) + " gets up from your lap.\n");

	in_lap->unset_no_show_composite();
	cleanup_rocker(TP);
	in_lap = 0;

	return 1;
    }
    else if (sitting == TP)
    {
	if (objectp(in_lap))
	{
	    in_lap->catch_msg(QCTNAME(TP) + " stands up, forcing you to "+
		"stand as well.\n");
	    tell_room(environment(), QCTNAME(in_lap) + " gets up from " +
		QTPNAME(TP) + " lap.\n", ({ TP, in_lap }));
	    TP->catch_msg(QCTNAME(in_lap) + " gets up from your lap.\n");

	    in_lap->unset_no_show_composite();
	    cleanup_rocker(in_lap);
	    in_lap = 0;
	}

	write("You get up from the "+ real_short() +".\n");
	tell_room(environment(), QCTNAME(TP) +" gets up from the "+
	    real_short() +".\n", ({ TP, in_lap }));

	TP->unset_no_show_composite();
	cleanup_rocker(TP);

	sitting = 0;
	return 1;
    }
    notify_fail("You don't appear to be seated.\n");
    return 0;
}

/*
 * Function name: do_sit
 * Description  : The function for sitting down.
 * Arguments    : The arguments for the command
 * Returns      : (int)1/0 - I handle this / Not my problem
 */
public int
do_sit(string str)
{
    object obj;

    if (!stringp(str) || str == "down" || str == "chair" || str == "rocker" ||
	parse_command(str, ({ }), "[down] [on] [the] [rocking] 'chair' / 'rocker'"))
    {
	if (sitting == TP)
	{
	    write("You lean further back into the "+
		real_short() +".\n");
	    say(QCTNAME(TP) + " leans further back into the "+
		real_short() +".\n");

	    return 1;
	}

	if (in_lap == TP)
	{
	    write("You are already sitting in "+
		sitting->query_the_possessive_name() +" lap!\n");
	    return 1;
	}

	if (environment() == TP)
	{
	    notify_fail("You can't sit in it while you are holding it.\n");
	    return 1;
	}

	if (sitting)
	{
	    notify_fail("It is already in use!\n");
	    return 0;
	}

	write("You lean back into the "+ real_short() +".\n");
	say(QCTNAME(TP) + " leans back into the "+
	    real_short() +".\n");

	sitting = TP;
	TP->set_no_show_composite(1);

	if (obj = clone_object(OBJ + "rocker_obj"))
	{
	    obj->move(TP, 1);
	    obj->set_rocker(TO);
	}

	return 1;
    }

    object *oblist = PARSE_THIS(str,
	"[on] / [in] [the] [lap] [of] [the] %l [lap]");

    if (!sizeof(oblist))
    {
	notify_fail("Sit where?\n");
	return 0;
    }

    if (sizeof(oblist) != 1)
    {
	notify_fail("Sit in whose lap? " +
	  "You can only sit in one person's lap at a time.\n");
	return 0;
    }

    if (sitting == TP)
    {
	write("You would need to stand up first!\n");
	return 1;
    }

    if (in_lap == TP)
    {
	TP->catch_msg("You readjust yourself on "+ QTPNAME(sitting) + " lap.\n");
	tell_room(environment(), QCTNAME(TP) + " readjust " +
	    QMET("query_objective", TP) + "self on " +
	    QTPNAME(sitting) +" lap.\n", ({ TP, sitting }));
	sitting->catch_msg(QCTNAME(TP) + " readjust " +
	    QMET("query_objective", TP) + "self in your lap.\n");
	return 1;
    }

    if (sitting != oblist[0])
    {
	notify_fail(oblist[0]->query_The_name(TP) + " is not seated.\n");
	return 0;
    }

    if (in_lap == oblist[0])
    {
	notify_fail(in_lap->query_The_name(TP) + " is already "+
	    "sitting in "+ sitting->query_the_possessive_name(TP) +
	    " lap!\n");
	return 0;
    }

    TP->catch_msg("You sit down in " + QTPNAME(sitting) + " lap.\n");
    tell_room(environment(), QCTNAME(TP) + " sits down in " +
	QTPNAME(sitting) + " lap.\n", ({ TP, sitting }));
    sitting->catch_msg(QCTNAME(TP) + " sits down in your lap.\n");

    TP->set_no_show_composite(1);
    in_lap = TP;

    if (obj = clone_object(OBJ + "rocker_obj"))
    {
	obj->move(TP, 1);
	obj->set_rocker(TO);
    }

    return 1;
}

public int
do_rock(string str)
{
    if (sitting == TP)
    {
	write("You rock in your "+ real_short() +".\n");
	say(QCTNAME(TP) +" rocks in "+
	    TP->query_possessive() + " rocking chair.\n");
	return 1;
    }
    else if (in_lap == TP)
    {
	write("You lean into "+ sitting->query_the_name(TP) +
	    ", causing the "+ real_short() +" to rock.\n");
	tell_room(environment(), QCTNAME(TP) + " leans into " +
	    QTNAME(sitting) + ", causing the "+ real_short() +
	   " tp rock.\n", ({ TP, sitting }));
	sitting->catch_msg(QCTNAME(TP) + " leans into you, "+
	    "causing the "+ real_short() +" to rock.\n");
	return 1;
    }

    notify_fail("Rock what?");
    return 0;
}

public void
init()
{
    ::init();

    add_action(do_sit,  "sit");
    add_action(do_sit,  "sink");
    add_action(do_rise, "stand");
    add_action(do_rise, "rise");
    add_action(do_rock, "rock");
}
