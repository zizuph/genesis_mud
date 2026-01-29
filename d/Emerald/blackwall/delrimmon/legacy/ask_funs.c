/*
 * Gnadnars conversation code from /d/Gondor/std/monster.c
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
 */
#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"


/* prototypes */
public varargs int	add_ask_item(mixed questions, mixed answers);
public void		set_default_answer(mixed answers);
public void		catch_question(string question);
public void		answer_question(mixed answers, int cmd);
public void		set_ask_log(string arg);
public string		echo_to_room(string arg);
public string		query_player();
public string		query_player_name();

/* global variables */
static string		Ask_log;
static int		Using_items;	/* set if using new style ask */

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
	/* backwards compat */
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


/* handy routines for embedded VBFC in answer strings */
public string	query_player() { return OB_NAME(TP); }
public string	query_player_name() { return TP->query_name(); }
public string	echo_to_room(string arg)
		{ tell_room(ENV(TO), arg+"\n"); return ""; }
