/*
 * Actors club symbol
 *
 * 2008-01-12 : Lunatari
 * + Logging of emotes disabled.
 * 2008-02-21 : Lunatari
 * + Thespian code basically removed.
 * 2008-03-14 : Gorboth
 * + Commented out all aspects of free emote. It has been moved to the
 *   Wise-persons club instead.
 */
#pragma strict_types

inherit "/std/object";

#include <macros.h>
#include <language.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <std.h>
#include <files.h>
#include <options.h>

#include "actor.h"

static int sHidden;

static nomask int do_ooc(string arg);
// static nomask int do_emote(string arg);
static nomask int do_help(string arg);
static nomask int do_tap(string arg);
static nomask int do_symbol(string arg);
static nomask mixed cat_string(mixed org, string what, object pl, int up);
static nomask mixed mk_item(object ob);
static nomask void tell_them(object ob, mixed arg);
static nomask int do_attend(string arg);
static nomask int do_suggest(string arg);
nomask void init_stuff();

/*
 * Name:	create_object
 * Desc:	Create the object, initialize variables etc.
 */
public nomask void
create_object()
{
    set_name("symbol");
    set_name("actor symbol");
    add_name(AC_TOKEN);

    set_long("It is a small symbol, showing a pair of ancient, miniature acting masks, bound together by a golden ribbon. One mask is white and has a happy face, while the other is black and has a sad face.\n");

    add_prop(OBJ_M_NO_DROP, "You cannot drop the symbol.\n");
    add_prop(OBJ_M_NO_BUY, "This symbol can't be sold or bought, only given as proof of mastership.\n");
    add_prop(OBJ_M_NO_GIVE, "You can't give it away, silly!\n");
    add_prop(OBJ_M_NO_SELL, "Sell the symbol of the club? What are you going to try to peddle next? Your soul???\n");
    add_prop(OBJ_M_NO_STEAL, "Hands off miscreant! The symbol is not for the likes of you!\n");
	     
    sHidden = 0;

    setuid();
    seteuid(getuid());

    /*
     * Allow display of member information
     */
    set_alarm(10.0, 0.0, &init_stuff());
}

/*
 * Name:	init_stuff
 * Desc:	Display some initial messages
 */
nomask void
init_stuff()
{
    string *suggested = AC_CENTRAL->list_suggest(1);
    string *nopromote;
    int last, prev_mess = 0;

    if (sizeof(suggested) != 0)
    {
	prev_mess = 1;

	TP->catch_msg("Your Actor's symbol suddenly starts vibrating and a soft voice can be heard:\n" +
		      "\nThe following players has been suggested for membership in the Actor's club:\n" + 
		      implode(map(map(suggested, capitalize), &operator(+)("  * ")), "\n") + "\n" + 
		      "  Keep an eye out for them and make your recommendations known on the inner\n" +
		      "  board in the club as soon as possible.\n");

	if (QUERY_LEVEL(TP) == ADMIN_RANK)
	{
	    suggested = AC_CENTRAL->list_suggest(-10);
	    
	    if (sizeof(suggested) != 0)
	    {
		TP->catch_msg("\nIn fact, the following players have been on the suggested list\n" +
			      "  for more than 10 days now:\n" + 
			      implode(map(map(suggested, capitalize), &operator(+)("  * ")), "\n") + "\n" + 
			      "  It's about time they either are accepted to the club or removed\n" +
			      "  from the list and notified of the fact.\n");
	    }
	}
    }
/*
    if (QUERY_LEVEL(TP) == ADMIN_RANK)
    {
		nopromote = AC_CENTRAL->rank_check(60, TRUSTED_RANK);

		if (sizeof(nopromote) != 0)
		{
			if (prev_mess == 0)
			TP->catch_msg("Your Actor's symbol suddenly starts vibrating and a soft voice can be heard:\n");
			
			TP->catch_msg("\nThe following people has been members for more than two months\n" +
				  "at their current level in the club:\n" + 
				  implode(map(map(nopromote, capitalize), &operator(+)("  * ")), "\n") + "\n" + 
				  "  Perhaps it's time for promotion or demotion? However, if in your\n" +
				  "  opinion that level is correct, perform the special command\n" +
				  "  'rankremain <name>' in order to inhibit this message for another\n" +
				  "  two months.\n");

			prev_mess = 1;
		}
    }
*/
    if ((time() - AC_CENTRAL->query_last_visit(TP->query_real_name())) > (30 * 24 * 60 * 60))
    {
	if (prev_mess == 0)
	    TP->catch_msg("Your Actor's symbol suddenly starts vibrating and a soft voice can be heard:\n");

	TP->catch_msg("\nIt's been over a month since you last visited the club domains.\n" +
		      "  Perhaps it would be a good idea to go over there soon just to check\n" +
		      "  the club bulletin board?\n");

	prev_mess = 1;
    }
    
    if (prev_mess == 1)
	TP->catch_msg("\n");
}

/*
 * Name:	show_subloc
 * Desc:	Show the symbol in a suitable way for people who look
 * Args:	subloc - the subloc
 *		me - The wearer
 *		for_obj - The watcher
 * Returns:	The show string
 */
public nomask string
show_subloc(string subloc, object me, object for_obj)
{
    string str;

    if (for_obj == me)
    {
        str = "You are wearing the symbol of the masks " +
            (sHidden ? "hidden" : "in plain view") + ".";

        if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        {
            return str + "\n";
        }

        return str + " Your rank is " + AC_RANK_NAMES[QUERY_LEVEL(me)] +
            ".\n";
    }

    if (!sHidden)
    {
        if (present(AC_TOKEN, for_obj))
        {
            return (capitalize(me->query_pronoun()) +
                " is wearing the symbol of the masks, with the special " +
                "insignia denoting the rank of " +
                AC_RANK_NAMES[QUERY_LEVEL(me)] + ".\n");
        }

        return capitalize(me->query_pronoun()) + " is wearing a symbol " +
            "consisting of two acting masks.\n";
    }

    if (present(AC_TOKEN, for_obj))
    {
        return (capitalize(me->query_pronoun()) + " carries " +
            me->query_objective() + "self with the air of a fellow actor.\n");
    }

    return "";
}

/*
 * Name:	init
 * Desc:	Initialize the commands, remove the symbol in case
 *		the wrong person gets it.
 */
public nomask void
init()
{
    if (environment(this_object()) != TP)
	return;

    if (SECURITY->query_wiz_rank(TP->query_real_name())	!= WIZ_MORTAL)
    {
	write("**** Important message from the Actors Club:\n\nUnfortunately you are a wizard. Wizards are considered to be permanently OOC and thus not suitable as members of the Actors Club. Welcome back later when your status has changed to a more humble position!\n");
	AC_CENTRAL->do_remove_member(TP->query_real_name(), REASON_WIZ);
	remove_object();
	return;
    }

    TP->add_subloc("the_actors_club", this_object());
    add_action(do_help, "help");
    add_action(do_ooc, "ooc");
    add_action(do_tap, "tap");
    add_action(do_symbol, "symbol");
    add_action(do_symbol, "actor");
    add_action(do_suggest, "suggest");
    add_action(do_attend, "attend");

//  if (QUERY_LEVEL(TP) >= EMOTE_RANK)
//      add_action(do_emote, "@");

    ::init();
}

/*
 * Name:	do_symbol
 * Desc:	Perform 'symbol' commands
 * Args:	arg - the argument string
 * Returns:	1 - success, 0 - not
 */
static nomask int
do_symbol(string arg)
{
    string *args;

    if (!stringp(arg))
	return notify_fail("Do what with the symbol?\n");

    args = explode(arg, " ");

    switch (args[0])
    {
    case "hide":
	if (sizeof(args) > 1 && args[1] == "on")
	{
	    write("You pin the symbol to the inside of your cloak, hiding it from public view.\n");
	    sHidden = 1;
	}
	if (sizeof(args) > 1 && args[1] == "off")
	{
	    write("You proudly pin the symbol to the front of your cloak, in plain view for anyone to see.\n");
	    sHidden = 0;
	}
	else
	    write("The symbol is " + (sHidden ? "hidden" : "in plain sight") + ".\n");
	break;

    default:
	return notify_fail("Do what with the symbol?\n");
	break;
    }
    return 1;
}

/*
 * Name:	do_help
 * Desc:	Perform help commands
 * Args:	arg - help on what
 * Returns:	1 - success, 0 - not
 */
static nomask int
do_help(string arg)
{
    string *args;

    if (!stringp(arg))
	return 0;

    args = explode(arg, " ");
    args += ({"help"});
    
    if (args[0] == "symbol" || args[0] == "actor")
    {
	switch (args[1])
	{
	case "help":
	    write("The symbol is the visible proof of your membership in the actors's club. It also provides you with a set of commands you carry with you at all times. These are:\n");
	    write("  'help'        - This help text, and help on any of the other commands, just type 'help symbol <command>'\n");
	    write("  'hide'        - Hide the symbol from public view.\n");
	    write("  'ooc'         - Out of character say.\n");
	    write("  'tap'         - Remind people that you are in character.\n");
	    write("  'suggest'     - Suggest new members for the club.\n");

	    if (QUERY_LEVEL(TP) >= MEMBER_RANK)
	    {
		write("  'attend'     - Call on all actors in Genesis to attend a meeting.\n");
	    }

//          if (QUERY_LEVEL(TP) >= EMOTE_RANK)
//              write("  '@'          - Free emotes.\n");

	    if (QUERY_LEVEL(TP) == ADMIN_RANK)
		write("  'rankremain' - Confirm someone's rank.\n");

	    break;

	case "hide":
	    write("The symbol can be hidden so that your membership becomes anonymous. Just type 'symbol hide on/off' as you please. Typing 'symol hide' shows the current setting. It's also possible to use the command 'actor hide on/off' in case of conflict with other objects.\n");
	    break;

	case "suggest":
	    if (QUERY_LEVEL(TP) >= MEMBER_RANK)
		write("With this command you can manage the list of potential new members for the club. Only members of rank Actor or higher have manipulation access to this command. Just type \"suggest\" to see the list, \"suggest <player name>\" to add someone and \"suggest remove <player name>\" to remove someone.\n");
	    else
		write("With this command you can display the list of suggested new members for the club.\n");
	    break;

	case "tap":
	    write("By typing 'tap symbol' you tap your fingers on the symbol (provided it's visible) thereby reminding people that you're in character. Do this when the surrounding conversation gets too OOC for your liking, or when someone tries to trick you into an OOC reply.\n");
	    break;

	case "ooc":
	    TP->more(AC_HELP + "ooc", 1);
	    break;

	case "attend":
	    if (QUERY_LEVEL(TP) >= MEMBER_RANK)
		write("With this command you issue a call to all currently present actors in Genesis to attend a meeting in the inner sanctum. Please respond to the call as quickly as possible. You can specify the subject of the meeting after the 'attend' command; e.g. 'attend Invitation of XXX to the club'.\n\nNB! Any message sent along this dedicated line is logged and subject to Thespian oversight, do not abuse it!\n");
	    else
		return notify_fail("No help on \"" + arg + "\" available.\n");
	    break;

	case "@":
	case "emote":
	    if (QUERY_LEVEL(TP) >= EMOTE_RANK)
		TP->more(AC_HELP + "emotes", 1);
	    else
		return notify_fail("No help on \"" + arg + "\" available.\n");
	    break;

	case "rankremain":
	    if (QUERY_LEVEL(TP) == ADMIN_RANK)
		write("With this command you confirm somone in his or her rank, so that you\n" +
		      "will not get a reminder to re-evalute that member's rank for another\n" +
		      "two months.\n");
	    else
		return notify_fail("No help on \"" + arg + "\" available.\n");
	    break;

	default:
	    return notify_fail("No help on \"" + arg + "\" available.\n");
	    break;
	}
	return 1;
    }

    return 0;
}

/*
 * Name:	do_tap
 * Desc:	Tap the symbol
 * Args:	arg - what to tap
 * Returns:	1 - success, 0 - not
 */
static nomask int
do_tap(string arg)
{
    if (arg != "symbol")
	return notify_fail("Tap what?\n");

    if (sHidden)
    {
	write("You tap your symbol furtively, hopefully gaining some sort of immense personal satisfaction from this secret act.\n");
	return 1;
    }

    if (TP->query_option(OPT_ECHO))
	write("You tap your actor's symbol, frowning a bit.\n");
    else
	write("Ok.\n");

    tell_room(environment(TP), QCTNAME(TP) + " taps the small symbol on " + TP->query_possessive() + " robe and frowns a bit, but says nothing.\n", TP);
    return 1;
}

/*
 * Name:	do_attend
 * Desc:	Call for a meeting of the club
 * Args:	The reason for the meeting	
 * Returns:	1 - success, 0 - not
 */
static nomask int
do_attend(string arg)
{
    string mess, *atts = ({});
    object *people;
    int i, sz;

    if (QUERY_LEVEL(TP) < MEMBER_RANK)
	return notify_fail("This command is only available to actors of rank " + AC_RANK_NAMES[MEMBER_RANK] + " and higher.\n");

    if (!strlen(arg))
	mess = capitalize(TP->query_real_name()) + " calls for a general meeting a the Actors club. Please come as soon as possible.\n";
    else
	mess =  capitalize(TP->query_real_name()) + " calls for a meeting a the Actors club, the subject of the meeting is '" + capitalize(arg) + "'. Please come as soon as possible.\n";

    for (i = 0, people = users(), sz = sizeof(people) ; i < sz ; i++)
    {
	if (CHECK_MEMBER(people[i]) && people[i] != TP)
	{
	    people[i]->catch_msg("The actor's symbol on your cloak whispers softly: " + mess);
	    atts += ({ people[i]->query_real_name() });
	}
    }

    if (sizeof(atts) > 0)
    {
	AC_CENTRAL->attend_call(TP->query_real_name(), arg, atts);
	write("" + sizeof(atts) + " actors heard your call.\n");
    }
    else
	write("No one heard your call at this time.\n");

    return 1;
}

/*
 * Name:	do_ooc
 * Desc:	Perform an ooc say
 * Args:	arg - Message
 * Returns:	1 - success, 0 - not
 */
static nomask int
do_ooc(string arg)
{
    tell_room(environment(TP), QCTNAME(TP) + " contorts " + TP->query_possessive() + " face into a rigid mask, and says in a flat tone of voice: " + arg + "\n", TP);
    if (TP->query_option(OPT_ECHO))
	write("You ooc: " + arg + "\n");
    else
	write("Ok.\n");
    return 1;
}

/*
 * Name:	do_emote
 * Desc:	Perform a club emote
 * Args:	arg - the emote with control chars
 * Returns:	1 - success, 0 - not
 *
 * I'm commenting this out. Do not add it back in without permission,
 * please! (Gorboth - Mar. 2008)
static nomask int
do_emote(string arg)
{
    object	pl, *pls, *seen;
    string	*args, *nms, oarg;
    int		i, sz, up;
    mapping	emap;

    if (QUERY_LEVEL(TP) < EMOTE_RANK)
	return notify_fail("This command is only available to actors of rank " + AC_RANK_NAMES[EMOTE_RANK] + " and higher.\n");
    
    pls = FILTER_LIVE(all_inventory(environment(TP))) - ({ TP });
    emap = mkmapping(pls, map(pls, mk_item));

    if (!stringp(arg))
	return notify_fail("Usage: @ <emote string>, emote string can contain names of present people enclosed in '|' characters, which then will be identified by their met/nonmet names to observers. e.g. '@ smile fondly at |madmartigan|'\n");

    oarg = arg;
    args = explode(arg, "|");

    emap = map(emap, &cat_string(, args[0], 0, 0));
    if ((sz = sizeof(args)) > 1)
    {
	for (i = 1 ; i < sz ; i ++)
	{
	    nms = explode(args[i], " ");
	    up = nms[0] == lower_case(nms[0]) ? 0 : 1;
	    nms[0] = lower_case(nms[0]);
	    if (objectp((pl = present(nms[0], environment(TP)))))
	    {
		emap = map(emap, &cat_string(, "", pl, up));
		if (sizeof(nms) > 1)
		{
		    arg = implode(nms[1..], " ");
		    emap = map(emap, &cat_string(, arg, 0, up));
		}
	    }
	    else if (i % 2)
		return notify_fail("You can`t see " + nms[0] + " here.\n");
	    else
		emap = map(emap, &cat_string(, args[i], 0, up));
	}
    }

    map(emap, &tell_them(TP, ));

    pls = filter(m_indices(emap), query_interactive);
    
    if (TP->query_option(OPT_ECHO))
	write("You emote: |" + capitalize(TP->query_real_name()) + "| " + oarg + "\n");
    else
	write("Ok.\n");
    
    //seen = filter(pls, &->check_seen(TP));
    //write_file(EMOTE_LOG + TP->query_real_name(), ctime(time()) + ": " + oarg + " [" + implode(sort_array(map(seen, capitalize @ &->query_real_name())), ", ") + "]\n");
    return 1;
}
*/

/*
 * Name:	do_suggest
 * Desc:	Manage list of suggested new members
 * Args:	str - suggest/unsuggest arguments
 * Returns:	1 - success, 0 - not
 */
public nomask int
do_suggest(string arg)
{
    string *args;

    if (QUERY_LEVEL(TP) < MEMBER_RANK)
    {
	AC_CENTRAL->list_suggest(0);
	return 1;
    }

    if (!strlen(arg))
    {
	AC_CENTRAL->list_suggest(0);
	return 1;
    }
    else
    {
	args = explode(arg, " ");
	if (args[0] == "remove")
	{
	    if (sizeof(args) == 2)
		return AC_CENTRAL->remove_suggest(lower_case(args[1]), TP->query_real_name());
	}
	else
	    return AC_CENTRAL->add_suggest(lower_case(args[0]), TP->query_real_name());
    }

    return notify_fail("Syntax: 'suggest'\n" +
		       "        'suggest <player name>'\n" +
		       "        'suggest remove <player name>'\n");
}

/*
 * Name:	do_rankremain
 * Desc:	Confirm someone in his rank
 * Args:	arg - whom to confirm
 * Returns:	1 - success, 0 - not
 *
public nomask int
do_rankremain(string arg)
{
    string name;

    if (QUERY_LEVEL(TP) != ADMIN_RANK)
	return 0;

    if (!strlen(arg))
	return notify_fail("Confirm who in his rank?\n");

    name = lower_case(arg);

    if (!CHECK_MEMBER_N(name))
    {
	notify_fail(capitalize(name) + " is not a member of the club.\n");
	return 0;
    }

    AC_CENTRAL->rank_remain(name, TP->query_real_name());

    return 1;
}*/

/*
 * Name:	query_auto_load
 * Desc:	Check if autoloading
 * Returns:     Object name + parameters
 */
public nomask string 
query_auto_load(void) 
{
    return MASTER_OB(this_object()) + ":" + sHidden;
}

/*
 * Name:	init_arg
 * Desc:	Perform conversions of restored init arguments
 * Args:	arg - the argument
 */
public nomask void
init_arg(string arg)
{
    sHidden = atoi(arg);
}

/*
 * Name:	enter_env
 * Desc:	The object enters an environment
 * Args:	to - To which object
 *		from - From which object
 */
public nomask void
enter_env(object to, object from)
{
    if (IS_PLAYER_OBJECT(to))
    {
	if (!CHECK_MEMBER(to))
	{
	    to->catch_msg("This is strange. You're not a member of the actor's club, so you shouldn't have a symbol either. Either this is a bug or you have been expelled from the club during your absence from the game. Please contact the club Thespians in case something is wrong. You ought to have a letter in the mail if you have been removed and this is not a bug.\n");
	    remove_object();
	    return;
	}

	AC_CENTRAL->login(to->query_real_name());
    }

    remove_name(AC_TOKEN);

    if (present(AC_TOKEN, environment(this_object())))
    {
        tell_room(environment(this_object()),
                  "The symbols melt together in some mysterious way.\n");
        set_alarm(1.0,0.0, &remove_object());
        return;
    }

    add_name(AC_TOKEN);

    ::enter_env(to, from);
}

/*
 * Name:	leave_env
 * Desc:	The object leaves an environment
 * Args:	old - From which object
 *		dest - To which object
 */
public nomask void
leave_env(object old, object dest)
{
	/*
    if (objectp(old) && IS_PLAYER_OBJECT(old))
    {
	  AC_CENTRAL->logout(old->query_real_name());
    }
    */
    ::leave_env(old, dest);
}

/*
 * Name:	cat_string
 * Desc:	Perform string conversions
 * Args:	Too complicated to explain
 * Returns:	The converted mixed
 */
static nomask mixed
cat_string(mixed org, string what, object pl, int up)
{
    if (objectp(pl))
	org[1] += (pl == org[0] ? (up == 1 ? "You" : "you") : (up == 1 ? QCTNAME(pl) : QTNAME(pl)));
    else
	org[1] += what;
    
    return org;
}

/*
 * Name:	mk_item
 * Desc:	Mapping function for converting object list to suitable array
 * Args:	ob - the object to convert
 * Returns:	The mixed array
 */
static nomask mixed
mk_item(object ob)
{
    return ({ ob, "" });
}

/*
 * Name:	tell_them
 * Desc:	Mapping function for telling all listeners in a group
 * Args:	ob - object to tell
 *		arg - what to tell
 */
static nomask void
tell_them(object ob, mixed arg)
{
    arg[0]->catch_msg(QCTNAME(ob) + " " + arg[1] + "\n");
}

/*
 * Name:	
 * Desc:	
 * Args:	
 * Returns:	
 */
