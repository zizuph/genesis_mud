/*
 * /d/Gondor/std/delay_room.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * inherits ~gondor/std/room, adds delayed cmd items.
 *
 * add_delay_cmd_item() is similar to add_cmd_item(), but instead of
 * immediately writing the results of the command, it writes a beginning
 * message, paralyzes the player for some period (similiar to the way
 * "search" paralyzes), then writes a finishing message.
 *
 * the prototype is:
 * public int	add_delay_cmd_item(mixed name, mixed verb, mixed stop_msg,
 *			mixed delay, mixed begin_msg, mixed finish_msg);
 * delay may be an integer or an array of integers, the others may be
 * a string or an array of strings.
 *
 * begin_msg and finish_msg may use VBFC. if the VBFC for the begin_msg
 * returns 0, the command fails.  begin_msg is responsible for doing the
 * appropriate calls to notify_fail(), in that case.
 *
 * if the room uses VBFC and keeps some state about who is doing the command,
 * then it must mask stop_delay_cmd(mixed arg) and, if arg is not an object
 * (i.e., the player did "stop"), unset the state.
 *
 * if begin_msg does not use VBFC, the message:
 *	QCTNAME(TP) + " begins " + stop_msg + "."
 * is displayed to the room.  it follows that stop_msg should be suitably
 * interesting ... e.g., "rummaging under the bed", rather than "rummaging"
 *
 * it is safe to use this_player() in begin_msg and finish_msg VBFC.
 *
 * see ~gondor/common/doc/examples/room_delay_cmd.c for an example.
 * 
 */

#pragma strict_types

#include "/d/Sparkle/sys/defs.h"

inherit S_BASE_ROOM;

#include <macros.h>
#include <stdproperties.h>


#define	MIN_DELAY		5
#define	LIVE_I_DELAY_ALARM	"_live_i_delay_alarm"

/* indices into messages, delays, etc use 0th element by default */
#define VALID_INDEX(i, s)	(i < s ? i : 0)
#define    ARRAY(v)        (pointerp(v) ? (v) : ({ (v) }))

/* indices into Delay_cmd_items */
#define	I_NAME		0
#define	I_VERB		1
#define	I_STOP		2
#define	I_DELAY		3
#define	I_BEGIN		4
#define	I_FINISH	5


static int	Outstanding_cmds,
		Leaving;
static mixed	Delay_cmd_items;
static string	*Delay_commands = ({ });


/* prototypes */
public void	init();
public void	leave_inv(object ob, object dest);
public int	add_delay_cmd_item(mixed name, mixed verb, mixed stop_msg,
			mixed delay, mixed begin_msg, mixed finish_msg);
public mixed	query_delay_cmd_item();
public int	remove_delay_cmd_item(string name);
public int	start_delay_cmd(string arg);
public int	stop_delay_cmd(mixed arg);
public void	finish_delay_cmd(object actor, mixed finish_msg);



/*
 * Function name:	init
 * Description	:	add all the delayed command verbs
 */
public void
init()
{
    int		s = sizeof(Delay_commands);

    ::init();
    while (s-- > 0)
    {
	add_action(start_delay_cmd, Delay_commands[s]);
    }
} /* init */


/*
 * Function name:	leave_inv
 * Description	:	mask parent so we are certain to remove alarms
 *			if player doing command somehow manages to leave
 * Arguments	:	object ob -- the departing object
 *			object dest -- its destination
 */
public void
leave_inv(object ob, object dest)
{
    Leaving = 1;
    stop_delay_cmd(ob);
    Leaving = 0;
    ::leave_inv(ob, dest);
} /* leave_inv */


/*
 * Function name:	add_delay_cmd_item
 * Description	:	adds item(s) with associated command(s) to
 *			be done after a delay, similar to 'search'
 * Arguments	:	mixed name -- a string or an array of strings,
 *				each of which is an item name.
 *			mixed verb -- a string or an array of strings,
 *				each of which is a command the player
 *				may use.
 *			mixed stop_msg -- a string or an array of strings,
 *				each of which is a msg displayed when
 *				the player does "stop". the msg passed
 *				here will have "You stop " prepended and
 *				".\n" appended, so a string such as 
 *				"rummaging under the bed" is what's needed.
 *			mixed delay -- an integer or an array of integers,
 *				each of which is time to delay (paralyzing
 *				the player) before the command completes.
 *			mixed begin_msg -- a string or an array of strings,
 *				each of which is the msg to display when
 *				the delay begins.
 *			mixed finish_msg -- a string or an array of strings,
 *				each of which is the msg to display when
 *				the command completes.
 * Returns	:	1 if successfully added, 0 if not
 *
 * begin_msg and finish_msg may use VBFC.  if begin_msg uses VBFC and
 * if the return is 0, the command will fail.  it is the responsibility
 * of the VBFC routine to do the appropriate calls to notify_fail()
 * before returning 0.
 */
public int
add_delay_cmd_item(mixed name, mixed verb, mixed stop_msg, mixed delay,
		   mixed begin_msg, mixed finish_msg)
{
    int		s;

    if (query_prop(ROOM_I_NO_EXTRA_ITEM))
    {
	return 0;
    }
    verb = ARRAY(verb);
    s = sizeof(delay = ARRAY(delay));
    while (s-- > 0)
    {
	delay[s] = MAX(delay[s], MIN_DELAY);
    }
    if (pointerp(Delay_cmd_items))
    {
	Delay_cmd_items += ({ ({ ARRAY(name), verb,
	    ARRAY(stop_msg), delay, ARRAY(begin_msg), ARRAY(finish_msg) }) });
    }
    else
    {
	Delay_cmd_items = ({ ({ ARRAY(name), verb,
	    ARRAY(stop_msg), delay, ARRAY(begin_msg), ARRAY(finish_msg) }) });
    }
    verb -= Delay_commands;
    Delay_commands += verb;
    return 1;
} /* add_delay_cmd_items */


public mixed	query_delay_cmd_item()	{ return Delay_cmd_items; }


/*
 * Function name:	remove_delay_cmd_item
 * Description	:	remove one command from the delayed commands list
 * Arguments	:	string name -- name of item to remove
 * Returns	:	1 if successfully removed, 0 if cannot be removed
 *			ever, -1 if cannot be removed right now (because
 *			we have a command running).
 */
public int
remove_delay_cmd_item(string name)
{
    int		i, j, n;
    string	*cmd_arr;

    if (!(n = sizeof(Delay_cmd_items)) ||
	query_prop(ROOM_I_NO_EXTRA_ITEM))
    {
	return 0;
    }
    if (Outstanding_cmds)
    {
	return -1;
    }
    for (i = 0; i < n; ++i)
    {
	if (member_array(name, Delay_cmd_items[i][I_NAME]) < 0)
	{
	    continue;	/* for */
	}
	Delay_cmd_items = exclude_array(Delay_cmd_items, i, i);
	--n;
	Delay_commands = ({});
	for (j = 0; j < n; ++j)
	{
	    /* not sure that this cmd_arr tmp var is needed, but
	     * it can't cost that much and they might have had good
	     * reason to do it this way ...
	     */
	    cmd_arr = Delay_cmd_items[j][I_VERB];
	    if (sizeof(cmd_arr))
	    {
		Delay_commands += (cmd_arr - Delay_commands);
	    }
	}
	return 1;
    }
    return 0;
} /* remove_delay_cmd_item */


/*
 * Function name:	start_delay_cmd
 * Description	:	find and start the delayed command for an item
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 if we understand the arg, 0 if not
 */
public int
start_delay_cmd(string arg)
{
    int		i, j, n,
		delay,
		pos;
    string	*words,
		verb,
		tmpstr;
    object	tp,
		paralyze;
	
    if (!(n = sizeof(Delay_cmd_items)))
    {
	return 0;
    }
    verb = query_verb();
    notify_fail(capitalize(verb) + " what?\n");
    if (!strlen(arg))
    {
	return 0;
    }
    arg = lower_case(arg);


    for (i = 0; i < n; ++i)
    {
	if ((pos = member_array(verb, Delay_cmd_items[i][I_VERB])) < 0)
	{
	    continue;	/* for */
	}
	words = Delay_cmd_items[i][I_NAME] + ({});
	if (parse_command(arg, ({}), "%p %s", words, tmpstr))
	{
	    gExcmd = tmpstr;
	    tp = TP;

	    /* write the you-begin msg.
	     * notice that this lets the room abort the command
	     * by returning 0 from VBFC.
	     */
	    j = VALID_INDEX(pos, sizeof(Delay_cmd_items[i][I_BEGIN]));
	    tmpstr = check_call(Delay_cmd_items[i][I_BEGIN][j]);
	    if (!tmpstr)
	    {
		continue; /* for */
	    }
	    if (stringp(tmpstr) &&
		strlen(tmpstr))
	    {
		write(tmpstr);
		if (stringp(Delay_cmd_items[i][I_BEGIN][j]) &&
		    tmpstr == Delay_cmd_items[i][I_BEGIN][j])
		{
		    /* not VBFC, so issue a default "Foo begins ..." msg */
		    j = VALID_INDEX(pos, sizeof(Delay_cmd_items[i][I_STOP]));
                    say(QCTNAME(this_player()) + " begins "
                      + Delay_cmd_items[i][I_STOP][j] + ".\n");
		}
	    }

	    /* start our alarm */
	    j = VALID_INDEX(pos, sizeof(Delay_cmd_items[i][I_DELAY]));
	    delay = Delay_cmd_items[i][I_DELAY][j];
	    j = VALID_INDEX(pos, sizeof(Delay_cmd_items[i][I_FINISH]));
	    tp->add_prop(LIVE_I_DELAY_ALARM,
		set_alarm(itof(delay), 0.0,
		    &finish_delay_cmd(tp, Delay_cmd_items[i][I_FINISH][j])));

	    /* paralyze 'em */
            setuid();
            seteuid(getuid());
	    paralyze = clone_object("/std/paralyze");
	    j = VALID_INDEX(pos, sizeof(Delay_cmd_items[i][I_STOP]));
	    paralyze->set_standard_paralyze(Delay_cmd_items[i][I_STOP][j]);
	    paralyze->set_stop_fun("stop_delay_cmd");
	    paralyze->set_remove_time(delay);
	    paralyze->move(tp, 1);
	    ++Outstanding_cmds;
	    return 1;
	}
    }
    return 0;
} /* start_delay_cmd */


/*
 * Function name:	stop_delay_cmd
 * Description	:	called when the paralyze time runs out, and 
 *			when the player does "stop"
 * Arguments	:	mixed arg -- if string, player did "stop"
 *				  -- if object, time ran out or
 *				      called from leave_inv().
 * Returns	:	0 -- stop is always allowed
 */
public int
stop_delay_cmd(mixed arg)
{
    int		alarm;
    object	tp;

    if (!objectp(arg))
    {
	/* called from paralyze object when player did "stop" */
	tp = environment(previous_object());
    }
    else if (Leaving)
    {
	/* called from this object's leave_inv */
	tp = arg;
    }
    /* else called from paralyze object when its time ran out, 
     * in which case we don't care
     */

    if (living(tp) &&
	(alarm = tp->query_prop(LIVE_I_DELAY_ALARM)))
    {
	remove_alarm(alarm);
	tp->remove_prop(LIVE_I_DELAY_ALARM);
	--Outstanding_cmds;
    }
    return 0;
} /* stop_delay_cmd */
	

/*
 * Function name:	finish_delay_cmd
 * Description	:	clear alarms, display finish_msg
 * Arguments	:	object actor -- the player doing the cmd
 *			mixed finish_msg -- the results. may be VBFC.
 */
public void
finish_delay_cmd(object actor, mixed finish_msg)
{
    object	save_tp;

    --Outstanding_cmds;
    if (!objectp(actor))
    {
	return;
    }
    actor->remove_prop(LIVE_I_DELAY_ALARM);

    /* set this_player so that if check_call is VBFC and they
     * want to mess with the player, they can.
     */
    save_tp = TP;
    set_this_player(actor);
    if (stringp(finish_msg = check_call(finish_msg)) &&
	strlen(finish_msg))
    {
	write(finish_msg);
    }
    set_this_player(save_tp);
} /* finish_delay_cmd */

