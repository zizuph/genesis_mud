/*
 * A bat messenger. Apparently people like bats as furry 
 * flying pup companions
 *
 * Created by Varian, February 2019
 */

#pragma strict_types

#include <macros.h>
#include <wa_types.h>

inherit "/std/messenger";
inherit "/std/act/action";

public int do_pet(string str);
public int do_poke(string str);
public int do_feed(string str);
public int do_disturb(string str);

void
create_messenger()
{
	set_name("bat");
	add_name("messenger");
	add_adj("small");
	add_adj("black");
	set_short("small, black bat");
	set_long("This small black bat appears to be comfortable " +
        "hanging around you. A small tube has been strapped to its " +
        "body so that it can carry a message from you to someone " +
        "else in the realms. Its soft, furry belly is irresistably " +
        "cute, and you feel almost compelled to pet the bat " +
        "gently. \n\nIf you want, you can <send> a " +
        "message to someone else in the realms by using this bat " +
        "as your messenger.\n");

	set_act_time(10);

    add_act("emote emits a soft, hungry-sounding squeak.");
    add_act("emote gently butts its furry head against your hand " +
        "hungrily.");
    add_act("emote snuggles up close to you as if wanting to be " +
        "petted.");
    add_act("emote wakes up briefly, stretching its wings " +
        "lethargically before settling back down, hoping to " +
        "not be disturbed.");
    add_act("emote suddenly lifts its small head to sniff the air " +
        "hungrily.");
    int i = add_hitloc(1, 25, "left wing", 0);    

    set_hitloc_unarmed(0,  1, 25, "right wing");
    set_hitloc_unarmed(1,  1, 25, "left wing");
    set_hitloc_unarmed(2,  1, 50, "head");
    
    set_attack_unarmed(1,  10, 10, W_IMPALE, 100, "bite");
}

public void 
init_living()
{
    if (!interactive(this_player())) {
        return;
    }

    ::init_living();

    add_action(do_pet, "pet");
    add_action(do_poke, "poke");
    add_action(do_feed, "feed");
    add_action(do_disturb, "disturb");
}

int
do_pet(string str)
{
    notify_fail("Pet what? Your bat?\n");
    if (!str || !strlen(str)) return 0;

    if (!id(str)) return 0; 

    write("You reach over to gently pet your bat, watching as it " +
    	"preens happily under your touch.\n");
    say(QCTNAME(this_player()) + " reaches over to gently pet a " +
        "small, black bat.");
    return 1;
}

int
do_poke(string str)
{
    notify_fail("Poke what? Your bat?\n");
    if (!str || !strlen(str)) return 0;

    if (!id(str)) return 0; 

    write("As you poke the soft, furry belly of the bat, you swear " +
        "you can feel the words 'BEWARE, I AM THE NIGHT!' echo in " +
        "your mind before it turns its head to look at you while " +
        "squeaking adorably.\n");
    say(QCTNAME(this_player()) + " pokes the small, black bat's " +
        "furry belly.");
    return 1;
}

int
do_feed(string str)
{
    notify_fail("Feed who? Your bat?\n");
    if (!str || !strlen(str)) return 0;

    if (!id(str)) return 0; 

    write("You prick your finger and squeeze a drop of blood into " +
        "the small, black bat's mouth.\n");
    say(QCTNAME(this_player()) + " pricks their finger and " +
        "squeezes a small drop of blood into the mouth of the " +
        "small, black bat.");
    return 1;
}

int
do_disturb(string str)
{
    notify_fail("Disturb who? Your bat?\n");
    if (!str || !strlen(str)) return 0;

    if (!id(str)) return 0; 

    write("You nudge the small, black bat who stretches its wings " +
    	"while screeching a high-pitched squeal before " +
    	"returning to its apparent slumber.\n");
    say("You wince as a nearby sudden high-pitched squeal hurts " +
    	"your ears.");
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
        " obediently takes the message and flies away.\n");
    say(QCTNAME(this_player()) + " gives a message to " + 
    	QTNAME(this_object()) + ". " + 
    	capitalize(this_object()->query_pronoun()) + 
    	" obediently takes the message and flies away.\n");
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
    	" obediently takes the message and flies away again.\n");
    say(QCTNAME(this_player()) + " convinces " + QTNAME(this_object())
        + " to try again. " + capitalize(this_object()->query_pronoun()) + 
        " obediently takes the message and flies away again.\n");
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
    	" flies up to " + QTNAME(sender) + ".\n", ({ sender }));   
}

/* 
 * Function name: hook_deliver_message_success
 * Description:   Description for successfully sending a message
 */
public void
hook_deliver_message_success(object receiver)
{
    receiver->catch_msg(QCTNAME(this_object()) + " flies up to you "
        + "with a message from " + capitalize(gSender) + ".\n");
    tell_room(environment(receiver), QCTNAME(this_object()) + 
    	" flies up to " + QTNAME(receiver) + ".\n", ({ receiver }));
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

    tell_room(room, QCTNAME(this_object()) + " flies away home.\n");
}
