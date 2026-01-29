/*
 *   This seems to be necessary nowadays, so here it goes:
 *
 *   You may do as you please with this code, but leave this and
 *   the next comment intact. That is, don't delete from it.
 *   Add all you want in the next comment.
 *                                                      Tricky
 */

/*
 *   Modified for genders: Padrone, Oct 22 1990
 *
 *   Initial Shires shield by Gobrus. (Changed to pipe by Tricky)
 *
 *   Severely modified for genders and using tobacco by Tricky, Feb 1-5, 1991
 *
 *   Further enhanced and split in two pieces (pipe and altar).
 *							Cheiron, Feb 1991
 *
 *   Small pipe changed. It now calls functions from the altar, instead
 *   of inheriting them, making the pipe much smaller.	Tricky, Mar 1991
 *
 *   3.0 functions added in advance by Cheiron, Mar 1991
 *
 *   Joined the pipe with the altar again to one object, because an object
 *   will only be loaded once, even if other people clone it.
 *							Tricky, Apr 1991
 * 
 *   Attempt to improve efficiency and clean up the code,
 *   including use of function word_wrap():		Cheiron, Jun 4, 1991
 *
 *   Finally installed a debug-mode, to relieve the players
 *   from nasty bugs while improving stuff related to the pipe.
 *   If you want to debug, define DEBUG as 1. All files that
 *   the pipe attempts to load will have to have "new" before
 *   them (not the shlist.o file). E.g. "hp.c" will in DEBUG
 *   mode be loaded from "newhp.c". The DEBUG-stuff is not compiled
 *   if DEBUG = 0.					Tricky, Jun 9, 1991
 *
 *   Hmmm... You turn your back and they install a brand new 3.0!
 *   Thoroughly rewritten for use with this new system. Tricky, Oct 7, 1991
 *
 *   Made the code slightly more readable by using standard indentation rules
 *   rules and thinking about adding more comments so people can revise the
 *   code more easily (Hmmm. Perhaps I did pick up something in that Software
 *   Engineering course... ;-) )		      Tricky, Jan 25, 1992
 *
 *   Added command 'newsoul' and mentioned it in pipe-help.
 *   Updates the hooks of everyone having the shire soul.
 *						      Nosferatu, May 16, 1992
 *
 *   Split pipe.c into pipe.c & pipe_include.h to keep the pipe-code
 *   under 50k each file... (maximum file size). Also moved level_info
 *   & pipe_help into files (in /d/Shire/common/guild/)
 *						      Nosferatu, May 18, 1992
 *
 *   Added (proto)types and added the pipe_spells.h includefile.
 *							Tricky, Jun 23, 1992
 *
 *   Added function compute_sacrifice_value() and re-coded do_sacrifice()
 *   so that it's now able to handle a sacrifice of multiple objects
 *                                                    Nosferatu, Aug 12, 1992
 *
 *   Re-coded do_throw_out() to do_expell() & throw_out_of_guild() in order
 *   to re-use the throwing code by do_sacrifice(). Also moved is_member()
 *   & is_a_shire() from pipe.c to pipe_include.h
 *                                                    Nosferatu, Aug 13, 1992
 *
 *   Added (query_invis && query_wiz) filter to do_show_members because
 *   players could still see if I was on when I was invisible.  That was
 *   sometime in December 1992.  Misc. comment and format changes, addition
 *   of MESG_MANA constant, added notify_fails to do_bonk, allowed argument
 *   "pipe" to the polish command, and changed the common
 *   capitalize(query_real_name()) to just query_name().  Also, found
 *   repeated code in init_msg() and do_train(), and redundant code in
 *   do_sacrifice_filter() and compute_sacrifice_value().
 *                                                         Astro, Feb 5, 1993
 *
 *   Threw out the general Shire-line, to save 10% in guildtax. Also made
 *   the `cure' and `tend' spells castable without ingredients, but with
 *   less effect.
 *                                                        Tricky, Apr 3, 1994
 *
 *   We're going to get a Council; added extra functions for them. Also,
 *   the message in the begin can adjusted by the Council if they like.
 *                                                        Tricky, May 8, 1994
 *
 *   We actually have a Council now, it works with this pipe, and the pipe
 *   works with it.
 *                                                        Tricky, Dec 19, 1994
 */

/*
 * TO DO:
 *	- Add tons of spells, including hide and shield
 *	- Make "help" for our own commands
 *	- Fill in all the function headers
 *	- Remove the addlist/rmlist/showlist commands, make a logfile
 *	  with all members.
 *      - Make the smoke time dependant, not use-once, smoke once.
 *      - Perhaps herbs can improve the effect of spells. So no forced use.
 *        (Don't like this one, though. Bad advertisement for herbs.)
 *      - Show invisibles to wizards (sl)
 *      - Why doesn't enlight work?
 */

/* See above for explanation */
#define DEBUG 0

inherit "/std/spells";

#include "/secure/std.h"
#include "/sys/tasks.h"
#include "/sys/macros.h"	/* Macros for nonmet players */
#include "/sys/wa_types.h"
#include "/sys/ss_types.h"
#include "/sys/cmdparse.h"	/* FIND_STR_IN_OBJECT()... Nice Nick! */
#include "/sys/language.h"	/* LANG_ADDART, LANG_PWORD and stuff  */
#include "/sys/stdproperties.h"
#include "defs.h"
#include "shire_defs.h"
#include <options.h>

/* Put special people in this array, they will become founders as well */
#define IS_SPECIAL ({ "cheiron", "elessar", "fatty" })

/* The domain that owns this object */
#define HOMEDOMAIN	"Shire"

/* The guild-bit information */
#define SB_GROUP	0
#define SB_BIT		0

/* Common constant in program, minimum mana for any sort of msg/emsg */
#define MESG_MANA 5

/* Where are all my objects? */
#define MYPATH "/d/Shire/common/guild/"

/* Unique id to identify the guildobject */
#define MY_UNIQUE_ID "shire_pipe"

/* outcomment this if you don't want it */
#define OWN_SOUL	MYPATH + "shire_soul_cmd"


#if DEBUG

#define LISTPOS		MYPATH + "newshlist"

#else

#define LISTPOS		MYPATH + "shlist"

#endif

#define GUILDPOS	MYPATH + "hguild"
#define STATUEPOS       MYPATH + "statue"

/* Declare all of these static */
static int 	used,
		online,		/* True if online on the shireline   */
		no_noise,	/* True if replace is to be silently */
		more_pos;

static string	filter_str,
	       *more_array;

/* Don't declare this static, so it can be saved */
string *banned; /* Array of banned people */

/*************************************************************************
 *
 *    Prototypes
 */

void add_shire_actions();
int query_online();
void init_msg(object who);
void set_offline();
int ghost();
int  fail_ghost();
static string *word_wrap(string str, int length);
void more_list();
void wait_for_more(string str);
object *who_known(object who);
object who_find(string str);
object find_known_player(string str);
void pipe_info();

/*
 * Special parts of the pipe
 */
#if DEBUG

#include "newpipe_include.h"	/* special commands for wizzes	*/
#include "newpipe_spells.h"	/* special spell part		*/

#else

#include "pipe_include.h"	/* special commands for wizzes	*/
#include "pipe_spells.h"	/* special spell part		*/

#endif

void
create_spells()
{
    seteuid(getuid());
    restore_object(LISTPOS);

    if (!IS_CLONE)
	return;

    seteuid("Shire");
    set_name("pipe");
    add_name(MY_UNIQUE_ID);
    set_pname("pipes");
    set_short("@@my_short"); /* Use own functions for short and long */
    set_pshort("@@my_pshort");
    set_long("@@my_long");
    used = 0;
    no_noise = 0;
    online = 1;
}

/*
 * Function name:   query_auto_load
 * Description:     Gives back a string of the form <filename>[:<arguments>]
 *                  where <filename> is the name of the object to autoload,
 *                  and <arguments> is a string with arguments that are to
 *                  be returned when the object autoloads
 * Returns:         Just that.
 * Arguments:       none.
 */
string
query_auto_load()
{
    if (online)
       return MASTER + ":online";
    return MASTER + ":offline";
}

/*
 * Function name:   init_arg
 * Description:     this function is called when the object is auto_loading
 *                  query_auto_load() returns a string of the form
 *                  <string>[:<arguments>]. When the object is autoloaded,
 *                  the arguments are passed to this function.
 * Arguments:       str: The argument put behind the autoload_string.
 */
void
init_arg(string str)
{
    if (str == "offline")
        online = 0;
    else
	online = 1;
}


/*
 * Function name:   my_pshort
 * Description:	    Gives back the plural short description of the pipe,
 *		    depending on the avarage stat of a player
 * Returns:	    The description
 */
string
my_pshort()
{
    int lev;

    lev = environment()->query_average_stat();
#if DEBUG
    return ("test-version of the pipe of the Shires");
#endif
    if (is_founder(environment()->query_real_name()))
	return ("impeccable pipes of the Shires");
    if (environment()->query_wiz_level())
	return ("adamant pipe of the Shires");
    if ((lev < 15) || (!is_a_shire(environment())))
	return ("wooden pipes of the Shires");
    if (lev < 20)
	return ("china pipes of the Shires");
    if (lev < 30)
	return ("marble pipes of the Shires");
    if (lev < 50)
	return ("silver pipes of the Shires");
    if (lev < 80)
	return ("golden pipes of the Shires");
    return ("platinum pipes of the Shires");
}

/*
 * Function name:   my_short
 * Description:	    Gives back the short description of the pipe,
 *		    depending on the avarage stat of a player
 * Returns:	    The description
 */
string
my_short()
{
    int lev;

    lev = environment()->query_average_stat();
#if DEBUG
    return ("test-version of the pipe of the Shires");
#endif
    if (is_founder(environment()->query_real_name()))
	return ("impeccable pipe of the Shires");
    if (environment()->query_wiz_level())
	return ("adamant pipe of the Shires");
    if ((lev < 15) || (!is_a_shire(environment())))
	return ("wooden pipe of the Shires");
    if (lev < 20)
	return ("china pipe of the Shires");
    if (lev < 30)
	return ("marble pipe of the Shires");
    if (lev < 50)
	return ("silver pipe of the Shires");
    if (lev < 80)
	return ("golden pipe of the Shires");
    return ("platinum pipe of the Shires");
}

/*
 * Function name:   my_long
 * Description:	    Gives back the long description of the pipe.
 * Returns:	    The description
 */
string
my_long()
{
    string str;
    str = "This is the magical pipe of the Hin warriors. "
	+ "If you are not a true Hin warrior, its use will be very limited. "
#if DEBUG
	+ "This is only a preliminary version of the pipe, "
	+ "ie. it is still in the test-phase. Expect bugs to happen. "
#endif
	+ "The pipe will tell you more with 'help pipe'.\n";
    return break_string(str,70);
}


/*
 * Function name:   init
 * Description:	    This function is called each time someone comes near
 *		    the pipe. Only the one who carries it get the commands
 *		    of the pipe, all others ought to be ignored.
 */
void
init()
{
    /* Check if it is the owner who causes this init */
    if (this_player() == environment())
    {
	add_shire_actions();
   set_alarm(1.0, 0.0, &init_msg(this_player()));
    }
}

/*
 * Function name:   add_shire_actions
 * Description:	    Add all commands that are not spells
 */
static void
add_shire_actions()
{
    add_action("do_spells", "spells", 0);
    add_action("do_smoke", "smoke", 0);
    add_action("do_smell", "smell", 0);
    add_action("do_bonk", "bonk", 0);
    add_action("do_leave", "leave", 0);
    add_action("do_polish", "polish", 0);
    add_action("do_enlight", "enlight", 0);
    add_action("do_give_explanation", "help", 0);
    add_action("do_destroy_pipe", "break", 0);
    add_action("do_online", "shon", 0);
    add_action("do_offline", "shoff", 0);
    add_action("do_message", "message", 0);
    add_action("do_message", "msg", 0);
    add_action("do_emessage", "emessage", 0);
    add_action("do_emessage", "emsg", 0);
    add_action("do_goto_board", "shireboard", 0);
    add_action("do_show_members", "sl", 0);
    add_action("do_show_members", "shirelist", 0);
    add_action("do_expell", "expell", 0);
    update_shire_spells();

#ifdef OWN_SOUL
    add_action("do_train", "train", 0);
#endif

     if (is_founder(this_player()->query_real_name()))
     {
	add_action("do_show_list", "showlist",0);
	add_action("do_remove_list", "rmlist",0);
	add_action("do_add_list", "addlist",0);
	add_action("do_replace", "replace",0);
	add_action("do_news", "news",0);
        add_action("do_newsoul", "newsoul", 0);
    }
}


/*
 * Communcation line procedures
 */

/*
 * Function name:   query_online
 * Returns:	    1 if the person is online
 *		    0 if offline
 */
int
query_online()
{
    return online;
}

/* Function name:   set_offline
 * Description:     silently turn Shireline off
 * Returns:         nothing (void)
 */
void
set_offline()
{
    online = 0;
}


/*
 * Function name:   do_online
 * Description:	    Turn the Shireline on.
 * Returns:	    Always 1.
 */
int
do_online(string str)
{
    online = 1;
    write("You are online again.\n");
    return 1;
}


/*
 * Function name:   do_offline
 * Description:	    Turn the Shireline off.
 * Returns:	    Always 1.
 */
int
do_offline(string str)
{
    online = 0;
    write("You are now offline.\n");
    return 1;
}

/*
 * Function name:   init_msg
 * Description:	    Give the intro-message and do some extra checks.
 *		    Also set most of the properties.
 *		    If the player is not allowed to have this pipe,
 *		    selfdestruct.
 * Arguments:	    who: The owner of the pipe.
 */
void
init_msg(object who)
{

            /* Closing down. */
                who->catch_msg("You hear a rumble from the Hin Mountain... "
                 + "You realize that the Hin Warriors are no more.\n"
                 + "The pipe disintegrates in a flash of light.\n");
                throw_out_of_guild(who, 0);
                remove_object();  /* Might happen automatically */
                return;


}

int
ghost()
{
    return environment()->query_ghost();
}

/***************************************************************************
 *
 *   Pipe functions for players.
 */


/*
 * Function name:   do_smoke
 * Description:     Smoke some flavour of tabacco.
 * Arguments:       str: The kind of tobacco one wants to smoke.
 * Returns:         1 on success.
 */
int
do_smoke(string str)
{
    object *tobacco, tp, env;
    string *flavours, flavour;

    if (ghost())
        return fail_ghost();

    tp = this_player();

    if (!is_a_shire(tp))
	return 0;

    if (!str)
    {
        notify_fail("Smoke what?\n");
        return 0;
    }

    if (str == "pipe")
    {
        if (this_player()->query_option(OPT_ECHO))
	{
	    write("You take out your pipe, and stuff it with some tobacco.\n"
		+ "You light the pipe, and puff out some beautiful smoke rings.\n");
	}
	else
	    write("Ok.\n");

	say(QCTNAME(tp) + " takes out " + tp->query_possessive() + " pipe, "
	    + "and stuffs it with tobacco.\n"
	    + CAP(tp->query_pronoun()) + " lights the pipe, and puffs "
	    + "out some beautiful smoke rings.\n", tp);
	return 1;
    }

    tobacco = FIND_STR_IN_OBJECT(str, tp);

    if (!sizeof(tobacco))
    {
        notify_fail("You don't have any " + str + ".\n");
        return 0;
    }

    if (sizeof(tobacco) > 1)
    {
        notify_fail("Could you be more specific?\n");
        return 0;
    }

    if (!(flavour = tobacco[0]->query_flavour()))
    {
        notify_fail("You only can smoke true Shire tobacco.\n");
        return 0;
    }

    if (this_player()->query_option(OPT_ECHO))
    {
        write("You take out your pipe, and stuff it with the " + flavour
	    + " tobacco.\n"
            + "You light the pipe, and puff out some beautiful smoke rings.\n");
    }
    else
	write("Ok.\n");

    say(QCTNAME(tp) + " takes out " + tp->query_possessive() + " pipe, "
        + "and stuffs it with tobacco.\n"
        + tp->query_pronoun() + " lights the pipe, and puffs out some "
        + "beautiful smoke rings.\n", tp);

    env = environment(tp);
    flavours = env->query_prop("_shire_smoked_flavours_");

    if (!flavours)
        flavours = ({ });

    env->add_prop("_shire_smell_times_", 10); /* You can smell it 10 times */

    /* Has this flavour been smoked before? */
    if (member_array(flavour, flavours) < 0)
        env->add_prop("_shire_smoked_flavours_", flavours + ({ flavour }));

    tobacco[0]->remove_object();	/* And remove the tobacco */
    return 1;
}

/*
 * Function name:   do_smell
 * Description:     Smell for flavour lingering in the air
 *                  One flavour can be smelled maximal ten times
 * Returns:         1 on success.
 */
int
do_smell(string str)
{
    int s, smell_times;
    object tp, env;
    string *flav;

    if (!is_a_shire(this_player()))
	return 0;

    if (str != "air" && str != "the air")
    {
        notify_fail("Perhaps you want to smell the air?\n");
        return 0;
    }

    tp = this_player();
    env = environment(tp);
    flav = env->query_prop("_shire_smoked_flavours_");

    write("You inhale the air deeply.\n");
    say(QCTNAME(tp) + " inhales the air deeply.\n", tp);



    if (!flav || !sizeof(flav))
    {
        write("You smell nothing in particular.\n");
        return 1;
    }

    smell_times = env->query_prop("_shire_smell_times_") - 1;

    if (smell_times <= 0)
    {
        write("You think you smell something, but then the scent is gone.\n");
        env->remove_prop("_shire_smoked_flavours_");
        env->remove_prop("_shire_smell_times_");
    }
    else
    {
        env->add_prop("_shire_smell_times_", smell_times);
        s = sizeof(flav);
        write("You smell a scent of ");

        if (s == 1)
            write(flav[0] + ".\n");
        else
            write(implode(flav[0..(s-2)],", ") + " and " + flav[s-1] + ".\n");
    }
    return 1;
}


/*
 * Function name:   do_polish
 * Description:	    simple emote
 * Arguments:	    str: what to polish
 * Returns:	    0 or 1
 */
int
do_polish(string str)
{
    object tp;

    if (strlen(str))
        if (str != "pipe")
	    return 0;

    if (ghost())
	return fail_ghost();

    tp = this_player();

    if (this_player()->query_option(OPT_ECHO))
	write("You polish your pipe to a fine gloss.\n");
    else
	write("Ok.\n");

    say(QCTNAME(tp) + " takes out a chamois, and polishes "
      + tp->query_possessive() + " pipe till it gleams!\n", tp);
    return 1;
}


#ifdef OWN_SOUL
/*
 * Function name:   do_train
 * Description:	    Allows a wizard to make any player a Shire member
 * Arguments:	    str: who to train
 * Returns:	    0 or 1
 */
int
do_train(string str)
{
    object who;
    int i;
    string *some_arr;
    string path, race;

    if (!is_a_shire(this_player()) || !str) return 0;
    if (this_player()->query_wiz_level() > WIZLEV_APPRENTICE)
    {
        /* Non-founders can only train players in same room */
	if (!is_founder(this_player()->query_real_name()))
	{
	    who = present(lower_case(str), environment(this_player()));
	    if (!who || !living(who) || who->query_npc())
		return 0;
	} 
	else
	{
	    who = find_player(lower_case(str));
	    if (!who)
		return 0; 
	}

	/* This doesn't work for wizards */
	if (who->query_wiz_level())
	{
	    write("It doesn't seem possible to train a fellow wizard.\n");
	    return 1;
	}
	who->catch_msg(QCTNAME(this_player()) + " gives you a real Hin Warrior training!\n");
	write("You flex your muscles and make " + capitalize(str)
	    + " do some pushups!\n");
	say(QCTNAME(this_player()) + " gives " + QCTNAME(who) + " a thorough Hin Warrior training!\n",
		 ({who,this_player()}));

	some_arr = who->query_cmdsoul_list();
	if(member_array(OWN_SOUL,some_arr) != -1)
	{
	    if (is_founder(this_player()->query_real_name()))
	    {
		if (who->remove_cmdsoul(OWN_SOUL))
		    write("You removed the Hin Warrior training from " + capitalize(str) + ".\n");
		else
		    write("You somehow failed to remove the Hin Warrior training from " + capitalize(str) + ".\n");
		return 1;
	    }
	    else
	    {
		write(capitalize(str) + " already looks trained.\n");
		return 1;
	    }
	}
	/* Filter out all known command souls */
	some_arr = filter(some_arr,"known_souls",this_object());

	if (!some_arr)
	    some_arr = ({ });

	/* Remove all command souls */
	for (i=0; i< sizeof(some_arr); i++)
	{
	    who->remove_cmdsoul(some_arr[i]);
	}

	/* Put the Shire-soul in front of the other souls */
	if (who->add_cmdsoul(OWN_SOUL))
	    write("You gave " + capitalize(str) + " a good training.\n");
	else
	    write("You gave " + capitalize(str) + " a good training, but failed.\n");

	/* Add all the other command souls */
	for (i=0; i< sizeof(some_arr); i++)
	{
	    who->add_cmdsoul(some_arr[i]);
	}
        who->update_hooks(); /* And make the souls active */
	return 1;
     }
     return 0;
}


/*
 * Function name:   known_souls
 * Description:	    This function will try to recognise other command
 *		    souls that we want to get rid of before we add
 *		    our own soul.
 * Arguments:	    str: The string to check whether it is a known soul
 * Returns:	    0 or 1
 */
int
known_souls(string str)
{
    string path, race;
    return (sscanf(str,"%ssoul_cmd_%s", path, race) == 2);
}
#endif

/*
 * Function name:   do_bonk
 * Description:	    simple emote
 * Arguments:	    str: who to bonk
 * Returns:	    0 or 1
 */
int
do_bonk(string str)
{
    object who;

    if (!str)
    {
        notify_fail("Who do you want to bonk?\n");
	return 0;
    }

    if (ghost())
	return fail_ghost();

    who = present(lower_case(str), environment(this_player()));

    if (!who || !living(who) || who == this_player())
    {
        notify_fail("That person doesn't seem to be here.\n");
	return 0;
    }

    who->catch_msg(QCTNAME(this_player()) + " bonks you with "
                 + this_player()->query_possessive()
                 + " pipe on the head!\n");

    if (this_player()->query_option(OPT_ECHO))
	this_player()->catch_msg("You bonk " + QCTNAME(who)
                           + " on the head with your pipe!\n");
    else
	write("Ok.\n");

    say(QCTNAME(this_player()) + " bonks " + QCTNAME(who)
      + " on the head with " + this_player()->query_possessive()
      + " pipe!\n",
		 ({who,this_player()}));
    return 1;
}


/*
 * Function name:   do_spells
 * Description:	    Updates the Shire-spells just before the player gets
 *		    to see them. This because this is the only way to do
 *		    the dynamic adding of spells while checking for her
 *		    stats.
 * Returns:	    Always 0, so the real "spells" command can take over.
 */
int
do_spells()
{
    update_shire_spells();
    return 0;
}


/*
 * Function name:   do_show_members
 * Description:	    list all visible and all non-wiz members of the guild
 *                  currently playing.
 * Returns:	    1
 */
int
do_show_members()
{
    string sh_name, sh_title, str;
    int i, cnt, lsize;
    object player_ob, active, pipe, *list;

    list = filter(users(),"is_member",this_object());
    lsize = sizeof(list);
    cnt = 0;
    write("Active Hin warriors are:\n");

    for (i=0; i < lsize; i++)
    {
	str = "";
	player_ob = list[i];

	/* Leave invisible people invisible to players */
	if (!(player_ob->query_invis()) ||
	    this_player()->query_wiz_level() >= WIZLEV_APPRENTICE)
        {
	    /* Everyone knows one another in the Shire */
	    if (!(sh_name = player_ob->query_name()))
		sh_name = "";

	    if (!(sh_title = player_ob->query_title()))
	        sh_title = "";

	    str = sh_name + " " + sh_title;

	    if (pipe = present(MY_UNIQUE_ID, player_ob))
	    {
	        if (pipe->query_online() == 0)
		    str += " <offline>";
	    }
	    else
		str += " (* no pipe *)";

	    if (player_ob->query_ghost())
	        str += " <deceased>";

	    /* Mark invisible players for wizards */
	    if (player_ob->query_invis() &&
		this_player()->query_wiz_level() >= WIZLEV_APPRENTICE)
		str = "(" + str + ")";

	    cnt++;	/* And another Hin warrior! */

	    this_player()->catch_msg(": " + str + "\n");
	}
    }
    write("Total number of active Hin warriors: " + cnt + ".\n"); 
    return 1;
}


/*
 * Function name:   do_message
 * Description:	    writes a "spoken" message to a single player; uses MESG_MANA
 * Arguments:	    str: string to write to other player
 * Returns:	    0 or 1
 */
int
do_message(string str)
{
    string who, c_who, msg, tell_str, known, impl_str;
    int is_wiz;
    object target, pipe;

    if (!str || !is_member(this_player()->query_name()))
	return 0;

    notify_fail("No such player!\n"
 	      + "Usage: msg <player> <text>\n");

    if ((sscanf(str, "%s %s", who, msg) != 2) || !who)
	return 0;

    is_wiz = this_player()->query_wiz_level();

    if (!is_wiz && this_player()->query_mana() < MESG_MANA)
    {
	write("You do not have enough mental power for that!\n");
	return 1;
    }

    who = lower_case(who);
    target = find_player(who);

    if (!target)
	return 0;

    if (target->query_wiz_level() &&
            ((target->query_prop(WIZARD_I_BUSY_LEVEL) & 8) ||
            (target->query_prop(WIZARD_I_BUSY_LEVEL) & 16) ||
            (target->query_prop(WIZARD_I_BUSY_LEVEL) & 128)))
    {
        write("That wizard is too busy to talk right now.\n");
        return 1;
    }
    else if (target->query_wiz_level() &&
            !(this_player()->query_wiz_level()) &&
            (target->query_prop(WIZARD_I_BUSY_LEVEL) & 4))
    {
        write("That wizard is too busy to talk right now.\n");
        return 1;
    }

    c_who = capitalize(who);

    if (!is_member(who))
    {
        write(c_who + " is not a Hin warrior!\n");
	return 1;
    }

    if (!(pipe = present(MY_UNIQUE_ID, target)))
    {
        write(c_who + " does not have a pipe!\n");
        return 1;
    }

    if (!is_wiz && target->query_wiz_level() && target->query_invis())
    {
        write("No such player!\n");
        return 1;
    }

    if (pipe->query_online() == 0)
    {
        write(c_who + " has turned the pipe offline!\n");
        return 1;
    }
    else
    {
        if (this_player()->query_option(OPT_ECHO))
	{
            /* Break the text and put stuff in between for yourself */
            write(":SHIRE: You tell " + c_who + ": "
             + implode(explode(break_string(msg, 55-strlen(c_who)),"\n"),
                             "\n:SHIRE: You tell " + c_who + ": ") + "\n");
	}
	else
	    write("Ok.\n");

        /* Break the text and put stuff in between for the recipient */
        if (this_player()->query_invis())
        {
	    /* Wizards get to see the invisible man or woman */
	    if (target->query_wiz_level() > WIZLEV_APPRENTICE)
		impl_str = ":SHIRE: (" + this_player()->query_name()
			 + ") tells you: ";
	    else
		impl_str = ":SHIRE: Someone tells you: ";
        }
        else
	    impl_str = ":SHIRE: " + this_player()->query_name()
		     + " tells you: ";

	tell_str = impl_str
		 + implode(explode(break_string(msg, 70-strlen(impl_str)),"\n"),
		   "\n" + impl_str) + "\n";
        target->catch_msg(tell_str);

        /* Reduce the mana */
        if (!is_wiz)
            this_player()->add_mana(-MESG_MANA);
    }
    return 1;
}


/*
 * Function name:   do_emessage
 * Description:	    Sends a personal emote to another player.
 * Arguments:	    A string with the adressee and the emotestring.
 * Returns:	    
 */
int
do_emessage(string str)
{
    string who, c_who, msg, tell_str, known, impl_str;
    int is_wiz;
    object target, pipe;

    notify_fail("No such player!\n"
 	      + "Usage: emsg <player> <feeling>\n");

    if (!str || !is_member(this_player()->query_name()))
	return 0;

    if ((sscanf(str, "%s %s", who, msg) != 2) || !who)
	return 0;

    is_wiz = this_player()->query_wiz_level();

    if (!is_wiz && this_player()->query_mana() < MESG_MANA)
    {
	write("You do not have enough mental power for that!\n");
	return 1;
    }

    who = lower_case(who);
    target = find_player(who);
    if (!target)
	return 0;

    if (target->query_wiz_level() &&
            ((target->query_prop(WIZARD_I_BUSY_LEVEL) & 8) ||
            (target->query_prop(WIZARD_I_BUSY_LEVEL) & 16) ||
            (target->query_prop(WIZARD_I_BUSY_LEVEL) & 128)))
    {
        write("That wizard is too busy to talk right now.\n");
        return 1;
    }
    else if (target->query_wiz_level() &&
            !(this_player()->query_wiz_level()) &&
            (target->query_prop(WIZARD_I_BUSY_LEVEL) & 4))
    {
        write("That wizard is too busy to talk right now.\n");
        return 1;
    }
    c_who = capitalize(who);
    if (!is_member(who))
    {
        write(c_who + " is not a Hin warrior!\n");
        return 1;
    }
    if (!(pipe = present(MY_UNIQUE_ID, target)))
    {
        write(c_who + " does not have a pipe!\n");
        return 1;
    }
    if (!is_wiz && target->query_wiz_level() && target->query_invis())
    {
        write("No such player!\n");
        return 1;
    }

    if (pipe->query_online() == 0)
    {
        write(c_who + " has turned the pipe offline!\n");
        return 1;
    }
    else
    {
        if (this_player()->query_option(OPT_ECHO))
	{
            /* Break the text and put stuff in between for yourself */
            write(":SHIRE: " + implode(explode(break_string("You tell " + c_who
	     + " \"" + this_player()->query_name()
             + " " + msg + "\"\n", 67), "\n"), "\n:SHIRE: ") + "\n");
	}
	else
	    write("Ok.");

        /* Break the text and put stuff in between for the recipient */
        if (this_player()->query_invis())
        {
	    if (target->query_wiz_level() >= WIZLEV_APPRENTICE)
		tell_str = "(" + this_player()->query_name()
			 + ") tells you that " + this_player()->query_pronoun()
			 + " " + msg + "\n";
	    else
		tell_str = "Someone tells you that "
                         + this_player()->query_pronoun() + " " + msg + "\n";
        }
        else
        {
	    tell_str = this_player()->query_name()
                 + " tells you that " + this_player()->query_pronoun()
                 + " " + msg + "\n";
        }
	impl_str = ":SHIRE: ";
	target->catch_msg(impl_str
		 + implode(explode(break_string(tell_str, 75-strlen(impl_str)),
			   "\n"), "\n" + impl_str) + "\n");

        /* Reduce the mana */
        if (!is_wiz)
            this_player()->add_mana(-MESG_MANA);
    }
    return 1;
}

/*
 * Function name:   fail_ghost
 * Description:	    writes a message to the dead player.
 * Arguments:	    none
 * Returns:	    Always 1
 */
int 
fail_ghost()
{
  write("You're a ghost!  You can't do that.\n");
  return 1;
}


/*
 * Function name:   do_destroy_pipe
 * Description:	    writes a message to the player (and others in the same
 *                    room) and removes the pipe.
 * Arguments:	    string str: what to break
 * Returns:	    1 if they did have a pipe, 0 otherwise.
 */
static int
do_destroy_pipe(string str)
{
    if (id(str))
    {
	write("As you break the pipe, it disintegrates in a flash of light.\n");
	say(QCTNAME(this_player()) + " breaks "
	  + this_player()->query_possessive() + " pipe...\n");
	remove_object();
	return 1;
    }
    return 0;
}


/*
 * Function name:   do_give_explanation
 * Description:	    gives help on pipe.
 * Arguments:	    string str:
 * Returns:	    1 or 0 (success or failure)
 */
int
do_give_explanation(string str)
{
    if (ghost())
	return fail_ghost();

    if (!str || (!is_a_shire(this_player()) && !(this_player()->query_wiz_level())))
	return 0;

    str = lower_case(str);

    if (id(str))
    {
	pipe_info();
	return 1;
    }

    if (str == "slevels")
    {
        seteuid(getuid());
        cat("/d/Shire/common/guild/pipe_help/level_info.txt");
	return 1;
    }
    if (str == "slevels2")
    {
        seteuid(getuid());
        cat("/d/Shire/common/guild/pipe_help/level_info2.txt");
	return 1;
    }
    return 0;
}


/*
 * Function name:   pipe_info
 * Description:	    shows player two or more of 6 help files.
 * Arguments:	    none
 * Returns:	    nothing (void)
 */
void
pipe_info()
{
    seteuid(getuid());

    if (is_a_shire(this_player()))
    {
	cat("/d/Shire/common/guild/pipe_help/pipe_help1.txt");
	if (this_player()->query_wiz_level() >= WIZLEV_NORMAL)
	    cat("/d/Shire/guild/pipe_help2.txt");
	if (this_player()->query_wiz_level() > WIZLEV_APPRENTICE) /* > ???*/
	    cat("/d/Shire/guild/pipe_help3.txt");
    }
    else
	cat("/d/Shire/common/guild/pipe_help/pipe_help4.txt");

    if (is_founder(this_player()->query_real_name()))
	cat("/d/Shire/common/guild/pipe_help/pipe_help5.txt");

    cat("/d/Shire/common/guild/pipe_help/pipe_help6.txt");
}


/*
 * Function name:   do_leave
 * Description:	    Tells player how to leave guild, and enables the action.
 * Arguments:	    str: string saying what to leave.
 * Returns:	    0 or 1
 */
static int
do_leave(string str)
{
    if ((!str) || str != "guild")
	return 0;

    write("Warning: this will not only destruct your pipe, but it will also\n"
	 + "get you off the memberlist. Are you sure you want to leave the\n"
	 + "guild? If you are, sacrifice a good armour or a good weapon.\n");

    add_action("do_sacrifice","sacrifice");
    return 1;
}

/*
 * Function name:   compute_sacrifice_value
 * Description:     This function computes the value of all objects in the
 *                  given array (obs).
 * Arguments:       obs: array of weapons and/or armors
 *                  MAKE SURE THIS IS TRUE!
 * Returns:         value
 */
int
compute_sacrifice_value(object *obs)
{
  int i, value;

  for (i = 0; i < sizeof(obs); i++)
  {
    switch (function_exists("create_object", obs[i])) /* Is this necessary with
                                                         do_sacrifice_filter? */
    {
      case "/std/armour":
        value += obs[i]->query_prop(OBJ_I_VALUE);
        break;
      case "/std/weapon":
        value += obs[i]->query_prop(OBJ_I_VALUE);
        break;
      default: return 0;
    }
  }
  return value;
}

/*
 * Function name:   do_sacrifice
 * Description:     This function allows you to leave the guild of the Shires
 *                  In order to leave the guild you must sacrifice one or more
 *                  valuable items.
 * Arguments:       str: Name of the carried valuable item(s)
 * Returns:         0 if the command is not recognised or accepted, else 1
 */
static int
do_sacrifice(string str)
{
  object *obs, ob;
  mixed *arr;
  int value, i;

  notify_fail("Sacrifice what?\n");
  if (!str) return 0;
  obs = FIND_STR_IN_OBJECT(str, this_player());
  if (!obs || !sizeof(obs)) return 0;
  obs = filter(obs, "do_sacrifice_filter", this_object());
  if (!obs || !sizeof(obs)) return 0;
  value = compute_sacrifice_value(obs);
  if (value < 500)
  {
    notify_fail("You must sacrifice a lot more than that.\n");
    return 0;
  }
  if (value < 1000)
  {
    notify_fail("Sorry, but it's not enough.\n");
    return 0;
  }
  write("Ok.\n");
  if (!throw_out_of_guild(this_player(), 0))
  {
    write("Something went wrong... Please contact a Shire wizard.\n");
    return 1;
  }
  for (i = 0; i < sizeof(obs); i++) obs[i]->remove_object();
  write("You are no longer a member of the Hin Warrior guild.\n");
  write("Your pipe disintegrates in a flash.\n");
  say(QCTNAME(this_player()) + " has left the Hin Warrior guild.\n");
  remove_object();
  return 1;
}

/*
 * Function name:   do_sacrifice_filter
 * Description:     a filter function for do_sacrifice()
 *                  filters out all non-armours and non-weapons
 * Arguments:       ob: object that needs to be checked out
 * Returns:         1 if suitable sacrifice or else 0
 */
int
do_sacrifice_filter(object ob)
{
  string str;

  str = function_exists("create_object", ob);
  return str == "/std/armour" || str == "/std/weapon";
}

/**********************	     Some useful functions *******************/

/*
 * Function name:   word_wrap
 * Description:	    This is basically break_string, only it gives back
 *		    an array of strings.
 * Arguments:	    str: The string to be cut
 *		    length: The length of the pieces
 * Returns:	    An array of lines shorter than "length".
 */
static string *
word_wrap(string str, int length)
{
    string *lines;

    lines = ({ });
    lines += explode(break_string(str + "\n", length), "\n");

    return lines;	/* return an array with the str cut into lines */
}

/*
 * Function name:   more_list
 * Description:	    Use more on an array. All elements of the global array
 *		    more_array will be printed in four rows. The starting
 *		    position of each column is counted by more_pos
 * Arguments:	    None, but more_array should contain some strings and
 *		    initially more_pos should be 0.
 */
void
more_list()
{
    string emptystr, fillstr;
    int array_size, count, lastlen;

    emptystr = "                     ";
    array_size = sizeof(more_array);
    count = lastlen = 0;
    while((more_pos < array_size) && (count < 88))
    {
	if ((count % 4) == 0)
	    write(more_array[more_pos]);
	else
	    write(extract(emptystr,0,19-lastlen) + more_array[more_pos]);
	lastlen = strlen(more_array[more_pos++]);
	if ((count++ % 4) == 3)
	    write("\n");
    }
    if (more_pos == array_size)
    {
	write("\n");
	return;
    }
    write("<More>   ");
    input_to("wait_for_more");
}


/*
 * Function name:   
 * Description:	    
 * Arguments:	    
 * Returns:	    
 */
void
wait_for_more(string str)
{
    if (str == "q" || str == "Q")
	return;
    more_list();
}

/*
 * Function name:    who_known
 * Description:	     Who of the players currently logged in are known?
 * Arguments:	     who: The object of the player who wants to find others
 * Returns:	     A list with all objects that obj knows.
 */
object *
who_known(object who)
{
    object *list;
    mapping rem;
    mixed *subl;

    if (who->query_wiz_level())
        return users();

    rem = who->query_remembered();
    if (mappingp(rem))
        list = map(m_indexes(rem), "who_find", this_object());
    else
        list = ({});

    rem = who->query_introduced();
    if (mappingp(rem))
    {
        subl = map(m_indexes(rem), "who_find", this_object());
        list = list + (sizeof(subl) ? subl : ({}));
    }
    if (sizeof(list))
        list = list + ({ who });
    else
        list = ({ who });

    list = list - ({ 0 });

    return list;
}


/*
 * Function name:   
 * Description:	    
 * Arguments:	    
 * Returns:	    
 */
object
who_find(string str)
{
    return find_living(str);
}

/*
 * Function name:   find_known_player
 * Description:	    Same as find_player, but only for known people
 * Arguments:	    str: The name of the player you search
 * Returns:	    0 if the player is not found, or not known
 *		    the player-object otherwise
 */
object
find_known_player(string str)
{
    object obj, *list;
    int i;

    obj = find_player(str);
    if (!obj)
	return 0;
    list = who_known(this_player());
    i = member_array(obj,list);
    if (i < 0)
	return 0;
    return obj;
}
