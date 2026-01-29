/*
 * /d/Gondor/std/monster.c
 *
 * /std/monster.c with a few functions added
 *
 * Copyright (C) 1997 Christian Markus and Wout de Zeeuw 
 *
 * Fysix + Olorin, February 1997
 *
 * Revision history:
 *  6 July 1998, Gnadnar: added money 
 * 13 October 1998, Gnadnar: do not call command() in arm_me()
 * 30 October 1998, Gnadnar: modified asking routines:
 *	add_ask_item()        -- add_ask() modified to accept multi-string 
 *			         answers and multiple answers
 *      set_default_answer()  -- accept multi-string and multiple answers
 *	catch_question()      -- strips leading "about" and "for" (as well
 *				 as trailing ? and .)
 *	answer_question()     -- if question has multiple answers, chooses
 *				 one at random. handle multi-string answers
 *	set_ask_log()         -- set name of log file for unknown questions
 *   plus these routines for VBFC inside a question:
 *	query_player()           -- returns OB_NAME(TP)
 *	query_player_name()      -- returns TP->query_name()
 *      echo_to_room(string arg) -- echos arg+"\n" to ENV(TO)
 * 5 December 2002, Gwyneth: Added intro routines.
 *      set_intro(float f, mixed m) -- 
 *                        f: Delay to introduce in response to player's intro.
 *                        m(optional): function to call instead of intro'ing
 *                           or an array of commands to perform.
 *                        ex. set_intro(1, ({ "say Hello", "introduce me" }));
 *                            set_intro(1, do_intro);
 */

#pragma strict_types

inherit "/std/monster.c";
inherit "/d/Gondor/common/lib/logkill.c";

#include <macros.h>
#include <money.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

/* prototypes */
public void		create_gondor_monster();
public void		create_monster();
public varargs void	arm_me();
public int		set_equipment(mixed arms);
public int		set_money(mixed moneys);
public varargs int	add_ask_item(mixed questions, mixed answers);
public void		set_default_answer(mixed answers);
public void		catch_question(string question);
public void		answer_question(mixed answers, int cmd);
public void		set_ask_log(string arg);
public string		echo_to_room(string arg);
public string		query_player();
public string		query_player_name();
public varargs void     set_intro(float f, mixed m);

/* global variables */
static string		*Equipment = ({ });
static int		*Money = ({ });
static string		Ask_log;
static int		Using_items;	/* set if using new style ask */
static float            Intro = -1.0;   /* -1.0, defaults to no intro */
static mixed            IntroRoutine;
static string           *HaveIntro = ({});


/*
 * Function name: create_gondor_monster
 * Description:   creator for monsters in Gondor
 */
public void
create_gondor_monster()
{
}

/*
 * Function name: create_monster
 * Description:   monster creator
 *                Note that create_monster() is not declared nomask
 *                here for backwards compatibility.
 */
public void
create_monster()
{
    FIX_EUID;
    create_gondor_monster();
}

/*
 * Function name: arm_me
 * Description:   clone, move, wield, wear armours and weapons;
 *		  clone and move money.
 *                the function is defined as varargs to permit
 *                arguments in inheriting npcs, eg npc_dunadan (qv)
 */
public varargs void
arm_me()
{
    object	*eq, save_tp;
    FIX_EUID;
    add_cmdsoul("/cmd/live/speech");
    update_hooks();
    if (sizeof(Equipment))
    {
	eq = map(Equipment, clone_object);
	eq->move(TO);

	/* the obvious thing to do here would be 
	 *       command("wear all"); command("wield all");
	 * however, that can prevent teams from following their leader,
	 * if a team leader moves into a room that is not yet loaded,
	 * and if that room clones up npcs and as part of their setup,
	 * the npcs call command(). npc->command() wipes out the
	 * verb stored by the player's action -- and that verb
	 * is needed for the team to know how to follow.
	 *
	 * so, we shouldn't call command() in any chain of actions
	 * when loading the room.  fake it as follows:
	 */
	save_tp = TP;
	set_this_player(TO);
	eq->wear_me();
	eq->wield_me();
	set_this_player(save_tp);
    }
    switch (sizeof(Money))
    {
    case 4:
	MONEY_MAKE_PC(Money[3])->move(TO);
	/* FALLTHRU */
    case 3:
	MONEY_MAKE_GC(Money[2])->move(TO);
	/* FALLTHRU */
    case 2:
	MONEY_MAKE_SC(Money[1])->move(TO);
	/* FALLTHRU */
    case 1:
	MONEY_MAKE_CC(Money[0])->move(TO);
	break;
    }
    Equipment = ({ });
    Money = ({ });
}

/*
 * Function name: set_equipment
 * Description:   Set up weapons and armours of the npc.
 * Arguments:     arms: string or array of strings containing filenames
 *                      for weapons and armour to be wielded/worn.
 *                Other objects may be added to the npc's inventory
 *                in this way, too.
 * Returns:       True if succeeded
 */
public int
set_equipment(mixed arms)
{
    if (arms && stringp(arms)) 
	arms = ({ arms });
    
    if (!pointerp(arms) || !sizeof(arms))
	return 0;

    Equipment += arms;

    // if in an environment already, wield/wear immediately,
    // otherwise wield/wear when moved	
    if (objectp(environment(TO)))
	arm_me();
    return 1;
}

/*
 * Function name: set_money
 * Description:   Set up money of the npc.
 * Arguments:     mixed moneys -- integer or array of integers.
 *		  if integer, is # of copper coins.  if array,
 *		  is ({ #copper, #silver, #gold, #platinum })
 * Returns:       True if succeeded
 */
public int
set_money(mixed moneys)
{
    if (moneys && intp(moneys)) 
	moneys = ({ moneys });
    
    if (!pointerp(moneys) || !sizeof(moneys))
	return 0;

    Money = moneys;

    // if in an environment already, instantiate immediately,
    // otherwise instantiate when moved	
    if (objectp(environment(TO)))
	arm_me();
    return 1;
}


/*
 * Function name:	add_ask_item
 * Description	:	Adds an question this mobile can answer.
 *			add_ask_item can be repeatedly called with
 *			new questions.
 * Arguments	:	mixed questions - a single string or an array of
 *					  strings holding the possible 
 *					  question(s) of the item.
 *			mixed answers -	  an answer or an array of answers.
 *					  see note below.
 * Returns	:	1 if the question is added successfully,
 *			0 if not (e.g., if questions or answers args are 
 *				  null)
 * Note:
 * an answer is a string or an array of strings, each of which will be
 * processed via TO->command() in turn. thus an answer can have just
 * one string:
 *	"say No, I cannot help you."
 * or several:
 *	({ "sigh", "say Go away.", "glare @@query_player@@" })
 *
 * if an array of answers added, then one will be chosen at random
 * each time the question is asked.
 *
 * for example, there are 3 possible answers to this question:
 *   add_ask_item( ({ "task", "job", "quest" }),
 *	           ({
 *		      "emote turns away in silence.",
 *	              "emote sneers: You are not worthy.",
 *	              ({ "emote gestures mysteriously.", 
 *		         "@@echo_to_room|There is a distant mutter of "+
 *			    thunder, and the air grows chill and heavy.@@", 
 *	              }),
 *	           }),
 *	         );
 * WARNING: if the question has only one answer, and that answer has 
 * multiple strings, then the answer strings must be inside ({ ({ ... }) }).
 * this:
 *	add_ask_item("test", ({ "sigh", "say Maybe.", "shrug" }) );
 * will be taken as having three different answers, each with one string.
 * this:
 *	add_ask_item("test", ({ ({ "sigh", "say Maybe.", "shrug" }) }) );
 * will be taken as having one answer composed of three strings.
 */
public varargs int
add_ask_item(mixed questions, mixed answers)
{
    int		i, n;

    Using_items = 1;
    if (!pointerp(questions))
    {
	if (!strlen(questions))
	{
	    return 0;
	}
	questions = ({ questions });
    }
    else if (!sizeof(questions))
    {
	return 0;
    }
    if (!pointerp(answers))
    {
	if (!strlen(answers))
	{
	    return 0;
	}
	answers = ({ answers });
    }
    else
    {
	/* turn string answers into arrays */
	for (i = 0, n = sizeof(answers); i < n; ++i)
	{
	    if (!pointerp(answers[i]))
	    {
		answers[i] = ({ answers[i] });
	    }
	}
    }

    if (pointerp(ask_arr))
    {
	ask_arr = ask_arr + ({ ({ questions, answers }) });
    }
    else
    {
	ask_arr = ({ ({ questions, answers }) });
    }
} /* add_ask_item */


/*
 * Function name:	set_default_answer
 * Description	:	sets the answer(s) to unrecognized questions
 * Arguments	:	mixed answers -	  an answer or an array of answers.
 *					  see note below.
 * Important!
 * To make this function work when added to your npc, you must define an add_ask_item()
 * before you define set_default_answer().
 *
 * Note:
 * an answer is a string or an array of strings, each of which will be processed
 * via TO->command() in turn. thus an answer can have just one string:
 *	"say No, I cannot help you."
 * or several:
 *	({ "sigh", "say Go away.", "glare @@query_player@@" })
 *
 * if an array of answers added, then one will be chosen at random
 * each time an unknown question is asked.
 *
 * WARNING: if the question has only one answer, and that answer has 
 * multiple strings, then the answer strings must be inside ({ ({ ... }) }).
 * this:
 *	set_default_answer( ({ "sigh", "say Maybe.", "shrug" }) );
 * will be taken as having three different answers, each with one string.
 * this:
 *	set_default_answer( ({ ({ "sigh", "say Maybe.", "shrug" }) }) );
 * will be taken as having one answer composed of three strings.
 */
public void
set_default_answer(mixed answers)
{
    int		i, n;

    if (!pointerp(answers))
    {
	if (!strlen(answers))
	{
	    return;
	}
	answers = ({ answers });
    }
    else
    {
	/* turn string answers into arrays */
	for (i = 0, n = sizeof(answers); i < n; ++i)
	{
	    if (!pointerp(answers[i]))
	    {
		answers[i] = ({ answers[i] });
	    }
	}
    }
    default_answer = answers;
} /* set_default_answer */


/*
 * Function name:	catch_question
 * Description	:	This function is called in each living being
 *			of which someone asks a question.
 * Arguments	:	question - The question as put
 */
public void
catch_question(string question)
{
    int		i, n;

    if (!Using_items)
    {
	/* backwards compat */
	::catch_question(question);
	return;
    }
    if (objectp(query_attack()))
    {
	return;	/* no answers if fighting */
    }

    if (dont_answer_unseen &&
	(!CAN_SEE(TO, TP) ||
	 !CAN_SEE_IN_ROOM(TO)))
    {
	set_alarm(rnd() * 3.0 + 1.0, 0.0, unseen_hook);
	return;
    }

    /* remove leading "for" or "about", and trailing " ?", "?" and "."  
     * (since we give them all the example of "What ?", i think players
     * might try a space in front of ?)
     */
    posed_question = lower_case(question);
    if (posed_question[0..3] == "for ")
    {
	posed_question = posed_question[4..];
    }
    if (posed_question[0..5] == "about ")
    {
	posed_question = posed_question[6..];
    }
    i = strlen(question) - 1;
    if (posed_question[(i-1)..] == " ?")
    {
	posed_question = posed_question[..(i-2)];
    }
    else if (posed_question[i..] == "." ||
	     posed_question[i..] == "?")
    {
	posed_question = posed_question[..(i-1)];
    }


    for (i = 0, n = sizeof(ask_arr); i < n; ++i)
    {
	if (member_array(posed_question, ask_arr[i][0]) >= 0)
	{
	    set_alarm((rnd() * 4.0), 0.0, &answer_question(ask_arr[i][1], 0));
	    return ;
	}
    }
    if (strlen(Ask_log))
    {
	log_file(Ask_log,
	    ctime(time()) + " " + file_name(this_object())+"\n\t" +
	    TP->query_real_name() + " asks:\t" + question + "\n");
    }
    if (default_answer)
    {
	set_alarm((rnd() * 4.0), 0.0, &answer_question(default_answer, 0));
    }
} /* catch_question */


/*
 * Function name:	answer_question
 * Description	:	This function is called after a short delay when
 *			this mobile wants to react to a question
 * Arguments	:	mixed answers -	  an answer or an array of answers.
 *					  see note below.
 *			int cmd - here for compat with parent, ignored.
 *					  
 * Note:
 * by this point, all answers are arrays of strings.
 * an answer can have just one string:
 *	({ "say No, I cannot help you." })
 * or several:
 *	({ "sigh", "say Go away.", "glare @@query_player@@" })
 *
 * if an array of answers added, then one will be chosen at random
 * each time the question is asked.
 *
 *
 */
public void
answer_question(mixed answers, int cmd)
{
    object	env = ENV(TO);
    mixed	chosen,
		result;
    int		i, n;

    if (!Using_items)
    {
	/* BAD BAD backward compatibility. The mudlib does not handle array
	 * answers. */
	if (pointerp(answers)) answers = one_of_list(answers);
	::answer_question(answers, cmd);
	return;
    }
    if (not_here_func &&
 	env != ENV(TP) &&
	env != TP &&
	!call_other(TO, not_here_func, TP))
    {
	return;
    }
    if (!(n = sizeof(answers)))
    {
	return;
    }
    if (!pointerp(answers[0]))
    {
	/* only one answer to this question */
	chosen = answers;
    }
    else
    {
	/* multiple answers -- choose one */
	chosen = answers[random(n)];
    }
    for (i = 0, n = sizeof(chosen); i < n; ++i)
    {
	if (stringp(result = TO->check_call(chosen[i], TP)) &&
	    result != "")
	{
	    command(result);
	}
    }
} /* answer_question */


/*
 * Function name:	set_ask_log
 * Description	:	cause unrecognized questions to be logged 
 * Arguments	:	string logfile -- the name of the log file,
 *			  relative to the domain's or wizard's log dir.
 */
public void
set_ask_log(string arg)
{
    Ask_log = arg;
} /* set_ask_log */


/*
 * Function name: set_intro
 * Description  : Allows an npc to introduce in response to a player's
 *                introduction, and optionally call a function or make
 *                the npc do something.
 *                ex. set_intro(1.5, ({ "say Hello", "introduce me" }));
 *                    set_intro(1.0, do_intro);
 *                    set_intro(2.3);
 *                    set_intro(); // Defaults to 1.0 delay
 *                NOTE: If you do include the second argument, you must
 *                have the npc introduce itself if you want it to within
 *                the second argument (as in the first example) or within
 *                the function called. This is to allow npcs like the
 *                Rangers who don't wish to introduce, but just wish to
 *                respond in a different way to an introduction.
 * Arguments    : f: Delay to introduce in response to player's intro.
 *                m: (optional) function to call instead of intro'ing
 *                   or an array of commands to perform.
 *                   The player object will be passed along as an
 *                   argument in a function call.
 */
public varargs void
set_intro(float f, mixed m)
{
    if (!floatp(f))
        Intro = 1.0;
    else if (f <= 10.0)
        Intro = f;
    else
        Intro = 10.0;

    if (functionp(m) || pointerp(m))
        IntroRoutine = m;
}

/*
 * Function name: intro_routine
 * Description  : Called to introduce the npc.
 * Arguments    : object player - the player to introduce to
 */
public void
intro_routine(object player)
{
    int i, size;

    if (!objectp(player) || !present(player, environment()))
        return;

    if (!pointerp(IntroRoutine))
        command("introduce myself to " + OB_NAME(player));
    else
        for (i = sizeof(IntroRoutine) - 1; i >= 0; i--)
            command(IntroRoutine[i]);

    HaveIntro += ({ player->query_real_name() });
    return;
}

/*
 * Function name: add_introduced
 * Description  : Called in the npc when someone has introduced.
 *                Will not react to npcs.
 * Arguments    : string str - the name of the introducer
 */
public void
add_introduced(string str)
{
    object player;

    if (!strlen(str))
        return;

    if (Intro < 0.0)
        return;

    str = lower_case(str);
    if (objectp(player = find_player(str)) &&
        member_array(str, HaveIntro) == -1)
    {
        if (functionp(IntroRoutine))
            set_alarm(Intro, 0.0, &IntroRoutine(player));
        else
            set_alarm(Intro, 0.0, &intro_routine(player));
    }
}

/* handy routines for embedded VBFC in answer strings */
public string	query_player() { return OB_NAME(TP); }
public string	query_player_name() { return TP->query_name(); }
public string	echo_to_room(string arg)
		{ tell_room(ENV(TO), arg+"\n"); return ""; }
