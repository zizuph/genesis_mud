#include <macros.h>

inherit "/std/messenger";

#define MESSAGE_OBJ     "/doc/examples/obj/message"

public void
create_messenger()
{
    set_name("Hermes");
    set_short("A winged snake");
    set_long("This is a winged snake, wearing a satchel.\n");
    
    set_can_deliver_indoors(1);
    set_can_deliver_unmet(1);
    set_message_object_file(MESSAGE_OBJ);
    set_number_of_uses(5);         
}

public void
hook_send_message()
{
    this_player()->catch_msg("You hand your message to "
        + QTNAME(this_object()) + ".\n");
    say(QCTNAME(this_player()) + " hands a message to " 
	+ this_player()->query_possessive() + " " 
	+ QSHORT(this_object()) + ".\n");
    tell_room(environment(this_player()), QCTNAME(this_object()) 
	+ " flies off to deliver a message.\n");	
}

public void
hook_resend_message()
{
    this_player()->catch_msg("You instruct " + QTNAME(this_object()) 
	+ " to make yet another try.\n");
    say(QCTNAME(this_player()) + " instructs " 
	+ this_player()->query_possessive() + " " + QSHORT(this_object()) 
	+ " to make yet another try.\n");
    tell_room(environment(this_player()), QCTNAME(this_object()) 
	+ " slithers off to deliver a message.\n");	
}

public void     
hook_deliver_message_failure(object sender)
{
    sender->catch_msg("Your " + QSHORT(this_object()) + " returns unable "
	+ "to find " + capitalize(gReceiver) + ".\n");
    tell_room(environment(sender), QCNAME(this_object()) + " arrives "
	+ "flying and hands " + QTNAME(sender) + " a message.\n", sender);
}

public void     
hook_deliver_message_success(object receiver)
{
    receiver->catch_msg(QCNAME(this_object()) + " arrives slithering and hands "
	+ "you a message from " + capitalize(gSender) + ".\n");
    tell_room(environment(receiver), QCNAME(this_object()) 
	+ " arrives slithering and hands " + QTNAME(receiver) 
	+ " a message.\n", receiver);
}

public void
hook_messenger_returns_home()
{
    object room;

    if (living(room = environment(this_object())))
    {
	room = environment(room);
    }
    tell_room(room, QCTNAME(this_object()) + " flies away.\n");
}

public void
hook_cannot_deliver_player_unavailable(string who)
{
    notify_fail(capitalize(LANG_THESHORT(this_object()))
       + " looks at you confusedly, unable to understand who " 
       + capitalize(who) + " is!\n");
}
