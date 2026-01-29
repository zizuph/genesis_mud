/*
 * Messengers for Faerie
 * By Finwe, August 2002
 *
 * Modification Log:
 *   Petros, 9/5/2008
 *     - fixed deliv_time so that if the recipient logs off while
 *       a message is being composed, a runtime error will not occur.
 *   Petros, 12/6/2008
 *     - Converted to use the new base messenger object
 */

#include "defs.h"
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <files.h>

//inherit "/w/petros/open/messenger/messenger";
inherit "/std/messenger";

// Defines
#define NOTE_OBJ     (MESS_DIR + "note")

// Global Variables
public int      return_alarm;

public void 
create_messenger()
{
    set_name("chipmunk");
    add_name("chipmunk messenger");
    set_gender(random(2));
    set_adj(({"brown-striped", "tan"}));
    set_short("brown-striped chipmunk");
    set_pshort("brown-striped chipmunks");
    set_long("This is a brown-striped tan chipmunk. It has been tamed " +
        "by the elves of Faerie to send and receive messages. The chipmunk " +
        "is primarily tan all over except for its cinnamon colored head, " +
        "and white feet and belly. There is a small tube carefully " +
        "wrapped around its neck.\n\nTo send a message, simply 'send " +
        "[player]'. You may also 'send reply' to respond to the last " +
        "message. When you are finished with the chipmunk, simply 'free' " +
        "the animal and it will dash off to the nearest tree.\n");
    add_item(({"tube", "message tube"}),
        "The tube is lightweight and camouflaged to match the fur of " +
        "the chipmunk. There is some writing engraved on it that reads: " +
        "To send a message, simply 'send [player]'. You may also 'send " +
        "reply' to respond to the last message. When you are finished " +
        "with the chipmunk, simply 'free' the animal and it will dash " +
        "off to the nearest tree.\n");
 
    add_prop(OBJ_I_WEIGHT,300);
    add_prop(OBJ_I_VOLUME,500);
    add_prop(CONT_I_WEIGHT,300);
    add_prop(CONT_I_VOLUME,500);
    add_prop(NPC_M_NO_ACCEPT_GIVE, " doesn't want anything from you.\n");

    set_act_time(30);
    add_act("emote chitters: squeak squeakin squeak squeakity.");
    add_act("emote chitters: squeakin squeak squeak squeakity.");
    add_act("emote chitters: squeak squeak squeak squeakin.");
    add_act("emote chitters: squeakity squeakin squeak squeak.");
    add_act("emote chitters: squeaker squeakin squeak squeak.");
    add_act("emote dashes around you, then back up onto your shoulder.");
    add_act("emote quickly cleans its face with its paws.");
    add_act("emote sniffs the air carefully.");
    add_act("emote looks around nervously.");
    
    set_message_object_file(NOTE_OBJ);
}

void init_living()
{
    ::init_living();
    add_action("return_home", "free");

}
public int 
return_home(string s)
{
    notify_fail("Free what?\n");
    if(!s || s != "chipmunk")
    {
        return 0;
    }
    
    return_messenger_home();
    return 1;
}
 
public void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);
    if (IS_LIVING_OBJECT(dest))
    {
        remove_alarm(return_alarm);
        return_alarm = 0;
    }
    else if((gMessage == "") && (IS_ROOM_OBJECT(dest)))
    {
        return_alarm = set_alarm(itof(random(10)), 0.0, return_messenger_home);
    }
}

public void
hook_send_message()
{
    write("You carefully roll up your message and insert it into the tube on the " + short()+
        ". It chitters excitedly and scampers off to deliver it.\n");
    say(QCTNAME(TP)+" carefully rolls up a message and inserts into a tube on " + QTNAME(this_object())+
        ". It chitters excitedly and scampers off to deliver it.\n");
}

public void
hook_resend_message()
{
    write("You convince the " + short() + " to try again. It chitters "
        + "excitedly and scampers off to deliver the message again.\n");
    say(QCTNAME(TP) + " convinces " + QTNAME(this_object()) + " to try "
        + "again. It chitters excitedly and scampers off to deliver "
        + "the message again.\n");
}

public void     
hook_deliver_message_failure(object sender)
{
    sender->catch_tell("Your " + short() + " returns, unable to find "
        + capitalize(gReceiver) + ".\n"); 
    tell_room(environment(sender),
      "A " + short() + " scampers up to " + QTNAME(sender) + ".\n", sender);
}

public void     
hook_deliver_message_success(object receiver)
{
    receiver->catch_msg(QCTNAME(this_object()) + " scampers up to you with "
        + "a message from " + capitalize(gSender) + ". You carefully "
        + "remove the note from the tube around its neck.\n"); 
    tell_room(environment(receiver),
      "A " + short() + " scampers up to " + QTNAME(receiver) + ".\n", 
      receiver);
}

 
public void
hook_messenger_returns_home()
{
    object room;
    
    if (living(room = environment()))
        room = environment(room);

    tell_room(room, QCTNAME(this_object()) + " chitters happily, and dashes "
        + "away.\n");
}

/*
 * Function:    hook_cannot_deliver_player_unavailable
 * Description: Hook that gets called to display that the messenger cannot
 *              deliver to someone who is either LD or not in the game.
 * Arguments:   who - the person the sender is trying to send to
 * Returns:     nothing
 */
public void
hook_cannot_deliver_player_unavailable(string who)
{
    notify_fail(capitalize(LANG_THESHORT(this_object()))
	    + " chitters at you confusedly, unable to understand who " 
	    + capitalize(who) + " is!\n");
}
