/*
 * A messenger from Dol Guldur
 *
 * Created by Varian, November 2020
 */

#pragma strict_types

#include <macros.h>

inherit "/std/messenger";

public int do_hit(string str);

void
create_messenger()
{
	set_name("a small orc runner");
	add_name( ({"messenger", "runner"}) );
	add_adj( ({"small", "orc", "fast"}) );

    set_race_name("orc");
    set_stats( ({15, 25, 15, 5, 5, 5}) );
    set_gender(G_MALE);

	set_short("small orc runner");
	set_long("This small orc looks like a fast runner, as he has been " +
        "recruited to run messages to people all over! He looks " +
        "rather nervous however, afraid that you might hit him. " +
        "\n\nIf you want, you can <send> a message to someone else in " +
        "the realms by using this orc runner as your messenger.\n");
}

public void 
init_living()
{
    if (!interactive(this_player())) {
        return;
    }

    ::init_living();

    add_action(do_hit, "hit");
}

int
do_hit(string str)
{
    notify_fail("Pet what? Your bat?\n");
    if (!str || !strlen(str)) return 0;

    if (!id(str)) return 0; 

    write("You swing your arm viciously, backhanding the small orc " +
        "runner to punish him for his insolence.\n");
    say(QCTNAME(this_player()) + " gives a vicious backhanded slap " +
        "to the face of a small orc runner.");
    return 1;
}


/* 
 * Function name: hook_send_message
 * Description:   Description for sending a message
 */
public void
hook_send_message()
{
    write("You give your message to " + 
    	this_object()->query_the_name(this_player()) + ". " +
        capitalize(this_object()->query_pronoun()) + 
        " obediently takes the message and runs off.\n");
    say(QCTNAME(this_player()) + " gives a message to " + 
    	QTNAME(this_object()) + ". " + 
    	capitalize(this_object()->query_pronoun()) + 
    	" obediently takes the message and runs off.\n");
}

/* 
 * Function name: hook_resend_message
 * Description:   Description for resending a message
 */
public void
hook_resend_message()
{
    write("You convince " + this_object()->query_the_name(this_player()) + 
    	" to try again. " + capitalize(this_object()->query_pronoun()) + 
    	" obediently takes the message and runs off again.\n");
    say(QCTNAME(this_player()) + " convinces " + QTNAME(this_object())
        + " to try again. " + capitalize(this_object()->query_pronoun()) + 
        " obediently takes the message and runs off again.\n");
}

/* 
 * Function name: hook_deliver_message_failure
 * Description:   Description for failing to send a message
 */
public void
hook_deliver_message_failure(object sender)
{
    sender->catch_tell("Your " + this_object()->short() + " returns,"+
    	"unable to find "+ capitalize(gReceiver) + ".\n");
    tell_room(environment(sender), QCTNAME(this_object()) + 
    	" runs up to " + QTNAME(sender) + ".\n", ({ sender }));   
}

/* 
 * Function name: hook_deliver_message_success
 * Description:   Description for successfully sending a message
 */
public void
hook_deliver_message_success(object receiver)
{
    receiver->catch_msg(QCTNAME(this_object()) + " runs up to you "
        + "with a message from " + capitalize(gSender) + ".\n");
    tell_room(environment(receiver), QCTNAME(this_object()) + 
    	" runs up to " + QTNAME(receiver) + ".\n", ({ receiver }));
}

/* 
 * Function name: hook_messenger_returns_home
 * Description:   Description for sending a messenger away
 */
public void
hook_messenger_returns_home()
{
    object room;
    if (living(room = environment()))
    {
        room = environment(room);
    }

    tell_room(room, QCTNAME(this_object()) + " takes off running back " +
        "to Dol Guldur.\n");
}