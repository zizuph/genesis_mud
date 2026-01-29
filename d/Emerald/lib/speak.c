/*
 * /d/Genesis/lib/speak.c
 *
 * Use this module to allow players to "speak", "chat", or "talk" to
 * npcs.
 *
 * Configuration functions:
 * ------------------------
 * set_speak() - A string or array of string responses to the "speak" command.
 *               If an array of more than than one responses is given, each
 *               successive response will be given when the conversation is
 *               "continued" by speaking with the npc again.
 *
 * Example usage:
 *
 * inherit "/std/monster";
 * inherit "/d/Genesis/lib/speak";
 *
 * void
 * create_monster()
 * {
 *     set_name("bob");
 *
 *     // Indicate how the npc should respond when spoken to
 *     set_speak(({ "I'm so glad you decided to speak with me!  It's can " +
 *                  "get quite lonely here by myself.",
 *                  "I've heard rumours that there is treasuer hidden in " +
 *                  "the mountains!" }));
 * }
 *
 * void 
 * init_living()
 * {
 *     ::init_living();
 *
 *     // Add the "speak" commands
 *     init_speak();
 * }
 */

#include <cmdparse.h>
#include <macros.h>

static string *speak_list = ({});
static mapping to_whom_ive_spoken = ([]);

/* Function name: set_speak
 * Description:   designate response(s) to attempts to "speak" to
 *                the npc.
 * Arguments:     mixed speak - a string or an array of strings which
 *                              the npc will "say".  If an array is
 *                              given, each successive attempt to
 *                              "speak" to the npc will cause the npc
 *                              to respond with the next string in the
 *                              array.
 * Returns:       1 - responses added
 *                0 - responses not added
 */
public int
set_speak(mixed speak)
{
    if (stringp(speak))
    {
        speak = ({ speak });
    }
  
    if (!pointerp(speak))
    {
        return 0;
    }
  
    speak_list = speak;
    return 1;
}

/* Function name: query_speak
 * Returns:       An array of strings, which are the npc's responses
 *                the the "speak" command
 */
public string *
query_speak()
{
    return speak_list;
}

// Redefine this to alter how the npc responds
public void
speak_hook(string what_to_say)
{
    command("say " + what_to_say);
} 

// respond to a "speak"
public void
continue_speak(object who)
{
    int where_to_start;
    string what_to_say;
  
    if (!present(who, environment()) || !sizeof(speak_list))
    {
        return;
    }
  
    where_to_start = to_whom_ive_spoken[who];
  
    if (where_to_start >= sizeof(speak_list))
    {
        where_to_start = 0;
    }
  
    set_this_player(who);
    what_to_say = this_object()->check_call(speak_list[where_to_start]);
  
    speak_hook(what_to_say);

    if (++where_to_start >= sizeof(speak_list))
    {
        to_whom_ive_spoken = m_delete(to_whom_ive_spoken, who);
    }
    else
    {
        to_whom_ive_spoken[who] = where_to_start;
    }
}

// redefine this to change the message when a conversation is started  
public void
start_conversation_hook(object who)
{
    say(QCTNAME(who) + " tries to start a conversation with " +
        QTNAME(this_object()) + ".\n");
}

// redefine this to change the message when a conversation is continued
public void
continue_conversation_hook(object who)
{
    say(QCTNAME(who) + " continues " + who->query_possessive() +
        " conversation with " + QTNAME(this_object()) + ".\n");
}

// start the response sequence
public void
do_speak(object who)
{
    to_whom_ive_spoken[who] ? continue_conversation_hook(who) :
	start_conversation_hook(who);
  
    set_alarm(1.0, 0.0, &continue_speak(who));
}

// this is the code for the "speak" command.
public int
speak(string str)
{
    object *who;
  
    if (!strlen(str) ||
        !sizeof(who = PARSE_THIS(str, "[with] / [to] [the] %l")))
    {
        notify_fail("Speak to whom?\n");
        return 0;
    }
  
    who->do_speak(this_player());
    
    return 1;
}

public void
init_speak()
{
    add_action(speak, "speak");
    add_action(speak, "chat");
    add_action(speak, "talk");
}
