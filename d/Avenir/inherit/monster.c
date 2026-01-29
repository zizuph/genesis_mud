/* -*-C++-*-
 * file name:     /d/Avenir/inherit/monster.c
 * creator(s):    Tepisch   1993
 * purpose:       Standard inheritable monster for Avenir.
 * note:          Note: Some functions from Krynn's monster.c 
 * Revised
 *		Nov 2007 Lucius: cleanups.
 *
 * It has functionality for knight prestige, kill thief, and parsing asks.
 * To parse asks, do the following:
 *    add_ask("[about] 'water'", "say I'm thirsty. Bring water.", 1);
 */
#pragma strict_types

inherit "/std/monster";

#include <macros.h>
#include <stdproperties.h>

private static int prestige;		/* The prestige changing variable */
private static string extra_long; 	/* Any extra long description set */

#define SUBLOC	"_my_extra_long_for_monster"


/*
 * Function name: create_monster
 * Description:   The standard create
 */
public void
create_monster(void)
{
    stats_to_acc_exp(); /* Set up correct xp */
    refresh_living();   /* Full mana, hp, and fatigue */
}

/* 
 * This is masked to allow for parse() style questions.
 */
public void
catch_question(string question)
{
    int i, j;

    if (dont_answer_unseen &&
	(!this_player()->check_seen(this_object()) ||
	    !CAN_SEE_IN_ROOM(this_object())))
    {
	set_alarm((rnd() * 3.0) + 1.0, 0.0, unseen_hook);
	return;
    }

    /* Strip trailing period of question mark. */
    if (wildmatch("*[.\\?]", question))
	question = extract(question, 0, -2);

    posed_question = lower_case(question);

    foreach(mixed *arr : ask_arr)
    {
	/* Found a straight string match. */
	if (member_array(posed_question, arr[0]) >= 0)
	{
	    set_alarm(rnd() * 4.0, 0.0,
		&answer_question(arr[1], arr[2]));
	    return;
	}

	/* Checking parseable bits. */
	string *rex = regexp(arr[0], "\\[.*\\]|'.*'");

	foreach(string pattern : rex)
	{
	    /* Not a match, skip. */
	    if (parse_command(posed_question, ({ }), pattern))
	    {
		set_alarm(rnd() * 4.0, 0.0,
		    &answer_question(arr[1], arr[2]));
		return;
	    }
	}
    }

    if (default_answer)
    {
	set_alarm(rnd() * 4.0, 0.0,
	    &answer_question(default_answer, default_answer_cmd));
    }
}

/*
 * Function name: set_knight_prestige
 * Description:   Set the prestige changing value in the mobile
 * Arguments:	  pres - the prestige, if > 0 it will add to the acc, if < 0
 *		  	 it will add to the stat.
 */
public void
set_knight_prestige(int pres)	{ prestige = pres; }

/*
 * Function name: query_knight_prestige
 * Description:	  Return the prestige this monster will affect a knight.
 * Returns:	  The prestige.
 */
public int
query_knight_prestige(void)	{ return prestige; }

/*
 * Function name: attacked_by
 * Description:	  This function is called when somebody attacks this object
 * Arguments:	  ob - The attacker
 */
public void
attacked_by(object attacker)
{
    ::attacked_by(attacker);

    foreach(object mate : query_team_others())
	mate->notify_ob_attacked_me(this_object(), attacker);
}

/*
 * Function name: help_friend
 * Description:   Help my friends by attacking their attacker
 * Arguments:     attacker - The person who attacked my friend
 */
public void
help_friend(object ob)
{    
    if (!query_attack() && present(ob, environment()))
	command("kill " + OB_NAME(ob));
}

/*
 * Function name: notify_ob_attacked_me
 * Description:   This is called when someone attacks a team member of mine
 * Arguments:     friend - My team mate
 *		  attacker - The attacker
 */
public void
notify_ob_attacked_me(object friend, object attacker)
{
    if (query_attack())
	return;

    if (random(10))
	set_alarm(rnd() + 0.5, 0.0, &help_friend(attacker));
}

/*
 * Function name: set_extra_long
 * Description:   Add an extra long description to the mobile 
 * Arguments:     str - The string
 */
public void
set_extra_long(string str)
{
    extra_long = str;
    add_subloc(SUBLOC, this_object());
}

/*
 * Function name: show_subloc
 * Description:   This function is called to get the extra str
 * Arguments:     subloc  - The name of this sublocation
 *		  me      - this_object()
 * 		  for_obj - Who wants this description
 * Returns:	  The extra string to write
 */
public string
show_subloc(string subloc, object me, object for_obj)
{
    if (subloc != SUBLOC)
	return ::show_subloc(subloc, me, for_obj);

    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	return "";

    return check_call(extra_long);
}

/* 
 * Function name: thief_fun
 * Description:   The default thief attack function.
 *		  Will be called if KILL_THIEF is set
 *		  (from common.h), and will execute one
 *		  of the creatures random cacts before
 *		  attacking the player.
 */
public void
thief_fun(object thief, object victim, object ob)
{
    string *acts = query_cact();

    if (sizeof(acts))
	set_alarm(1.5, 0.0, &command(one_of_list(acts)));

    set_alarm(3.0, 0.0, &command("kill "+ OB_NAME(thief)));
}
