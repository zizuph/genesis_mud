/*
 * Example Creature Messenger
 *
 * This is a creature messenger based on the standard messenger class.
 * It shows how easy it is to create and customize messengers. Follow
 * this example if you wish to create a messenger quickly. If you need
 * to customize or add messenger functionality to an existing class,
 * then you should see humanoid_messenger.c.
 *
 * Created January 2009 by Petros
 */

#include <macros.h>

inherit "/std/messenger";

#define MESSAGE_OBJ     "/doc/examples/obj/message"

/*
 * Function:    create_messenger
 * Description: Set all the options in this function. It overrides the
 *              defaults set in init_messenger since it is the last
 *              function called by init_messenger.
 */
public void
create_messenger()
{
    set_name("messenger");
    set_short("example creature messenger");
    set_long("This is an example creature messenger.\n");
    
    set_can_deliver_indoors(1);
    set_can_deliver_unmet(1);
    set_message_object_file(MESSAGE_OBJ);
    set_number_of_uses(5);         
}

/* HOOKS TO CUSTOMIZE MESSAGES */

/*
 * Function:    hook_send_message
 * Description: Hook that gets called to display the message of the
 *              messenger getting the message and leaving to deliver it
 */
public void
hook_send_message()
{
    this_player()->catch_msg("You hand your message to "
        + QTNAME(this_object()) + ".\n");
    say(QCTNAME(this_player()) + " hands a message to " 
	+ this_player()->query_possessive() + " " 
	+ QSHORT(this_object()) + ".\n");
    tell_room(environment(this_player()), QCTNAME(this_object()) 
	+ " jogs off to deliver a message.\n");	
}

/*
 * Function:    hook_resend_message
 * Description: Hook that gets called to display the message of the
 *              messenger being asked to re-deliver after a failed attempt.
 */
public void
hook_resend_message()
{
    this_player()->catch_msg("You instruct " + QTNAME(this_object()) 
	+ " to make yet another try.\n");
    say(QCTNAME(this_player()) + " instructs " 
	+ this_player()->query_possessive() + " " + QSHORT(this_object()) 
	+ " to make yet another try.\n");
    tell_room(environment(this_player()), QCTNAME(this_object()) 
	+ " jogs off to deliver a message.\n");	
}

/*
 * Function:    hook_deliver_message_failure
 * Description: Hook that gets called to display the message of the
 *              the messenger being unable to deliver the message and
 *              returning to the sender.
 * Arguments:   sender - the person who sent the message
 */
public void     
hook_deliver_message_failure(object sender)
{
    sender->catch_msg("Your " + QSHORT(this_object()) + " returns unable "
	+ "to find " + capitalize(gReceiver) + ".\n");
    tell_room(environment(sender), QCNAME(this_object()) + " arrives "
	+ "jogging and hands " + QTNAME(sender) + " a message.\n", sender);
}

/*
 * Function:    hook_deliver_message_success
 * Description: Hook that gets called to display the message of the
 *              messenger successfully delivering the message to the
 *              recipient.
 * Arguments:   receiver - the person receiving the message
 */
public void     
hook_deliver_message_success(object receiver)
{
    receiver->catch_msg(QCNAME(this_object()) + " arrives jogging and hands "
	+ "you a message from " + capitalize(gSender) + ".\n");
    tell_room(environment(receiver), QCNAME(this_object()) 
	+ " arrives jogging and hands " + QTNAME(receiver) 
	+ " a message.\n", receiver);
}

/*
 * Function:    hook_messenger_returns_home
 * Description: Hook that gets called to display the message of the
 *              messenger returning home after either being used up or
 *              being asked to return home.
 */
public void
hook_messenger_returns_home()
{
    object room;

    if (living(room = environment(this_object())))
    {
	room = environment(room);
    }
    tell_room(room, QCTNAME(this_object()) + " jogs away.\n");
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
       + " looks at you confusedly, unable to understand who " 
       + capitalize(who) + " is!\n");
}
