/*
   /d/Kalad/lib/speak.c

   Inherit this file if you npc needs to be talked to.

   Fysix@Genesis, Oct 1997
 */
#pragma strict_types
#pragma save_binary

#include <macros.h>
#include <filter_funs.h>
#include <cmdparse.h>

// --- Globals ---
static string Speak_msg;

/* Function name: set_speak
 * Description:   Set the reply to give when someone is speaking to
 *                this npc.
 * Arguments:     string
 */
public void
set_speak(string s)
{
    Speak_msg = s;
}

/* Function name: query_speak
 * Description:   What is the reply this npc is gonna give when it is
 *                spoken to?
 * Returns:       string
 */
public string
query_speak()
{
    return Speak_msg;
}

/* Function name: default_response
 * Description:   Default response when somebody speaks to this npc.
 * Arguments:     object living, the one who tried to speak
 */
public void
default_response(object living)
{
    living->catch_msg("You speak briefly with " +
      QTNAME(this_object()) +
      " but get a sinking feeling that " +
      this_object()->query_pronoun() + " isn't going to respond.\n");
    tell_room(environment(), QCTNAME(living) + " tries to strike up a " +
      "conversation with " + QTNAME(this_object()) +
      " but gets no response.\n", living);
}

/* Function name: do_speak
 * Description:   Reply when someone is speaking to this npc.
 * Arguments:     object speak to whom?
 * Returns:       int 1.
 */
public int
do_speak(object living)
{
    if (Speak_msg)
    {
	living->catch_msg("You talk for a while with " +
	  QTNAME(this_object()) +
	  ", about trivial matters. " +
	  "Eventually " + this_object()->query_pronoun() + " says:\n" +
	  query_speak());
	tell_room(environment(living), QCTNAME(living) +
	  " starts speaking with " + QTNAME(this_object()) +
	  " but you can't hear what they are saying.\n", living);
	return 1;
    }

    default_response(living);
    return 1;
}

/* Function name: speak
 * Description:   Speak with this living.
 * Arguments:     string str
 * Returns:       1 if successful
 */
int
speak(string str)
{
    object   *livings;
    string   who;

    notify_fail(capitalize(query_verb()) + " with whom?\n");
    if (!str || !sizeof(livings = COMMAND_DRIVER->parse_this(str,
	  "[to] / [with] [the] %l")))
	return 0;

    if (sizeof(livings) > 1)
    {
	notify_fail("You can " + query_verb() + " with one person " +
	  "at a time only.\n");
	return 0;
    }

    // Try to speak with the living   
    if (!livings[0]->do_speak(this_player()))
	return 0;

    return 1;
}

/* Function name: init_speak
 * Description:   Add several actions for speaking with an npc.
 */
public void
init_speak()
{
    add_action(speak, "speak");
    add_action(speak, "chat");
    add_action(speak, "talk");
}
