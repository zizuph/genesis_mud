/*
 *  Messenger creature summoned by the ramar spell.
 *
 *  Arman Kharas, May 2018
 */

#pragma save_binary

inherit "/std/messenger";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include "/d/Shire/defs.h"

string *gAdj1 = ({ "black", "white", "silver", "charcoal",
    "black-chested", "golden", "tawny", "brown", "white-tailed" });

string *gAdj2 = ({ "noble", "solitary", "crested", "mountain",
    "long-crested", "crowned", "imperial", "magnificent", "dignified" });

string adj1, adj2;

#ifndef ONE_OF
#define ONE_OF(x)   (x[random(sizeof(x))])
#endif

void 
create_messenger()
{
    set_name("eagle");
    set_race_name("eagle");

    adj1 = ONE_OF(gAdj1);
    set_adj(adj1);
    adj2 = ONE_OF(gAdj2);
    set_adj(adj2);

    set_short(adj2+ " " +adj1+ " eagle");
    set_pshort(adj2+ " " +adj1+ " eagles");
    set_long("This is " +LANG_ART(adj2)+ " " +adj2+ " " +adj1+ 
        " eagle, a common cousin to the ancient Great Eagles sent " +
        "by Manwe to Middle-Earth to watch upon Morgoth. While not as " +
        "grand in size as a Great Eagle, this eagle is no less proud " +
        "or noble-hearted - willing to serve as a messenger in " +
        "the battle against darkness. You may 'send <name>' " +
        "a message with this eagle.\n");

    add_prop(OBJ_I_WEIGHT,350);
    add_prop(CONT_I_WEIGHT,350);
    add_prop(OBJ_I_VOLUME,350);
    add_prop(CONT_I_VOLUME,350);
    add_prop(OBJ_I_NO_GET,0);
    add_prop(OBJ_I_NO_DROP,0);
    add_prop(NPC_I_NO_LOOKS,1);
    add_prop(NPC_M_NO_ACCEPT_GIVE," is quite unable to carry " +
        "anything except a small note.\n");

    set_attack_unarmed(1, 5, 5, W_IMPALE, 100, "beak");
    set_hitloc_unarmed(1, ({ 5, 7, 3}), 100, "body");

    set_can_deliver_indoors(0);
    set_can_deliver_unmet(1);
}

// HOOKS TO BE DEFINED

/*
 * Function:    hook_cannot_deliver_player_unavailable
 * Description: Hook that gets called to display that the messenger cannot
 *              deliver to someone who is not in the game. Set a notify_fail()
                message.
 * Arguments:   string who - name of the recipient.
 */
public void
hook_cannot_deliver_player_unavailable(string who)
{
    notify_fail(this_object()->query_The_name(this_player())
       + " does not understand who " 
       + capitalize(who) + " is!\n");
}

/*
 * Function:    hook_cannot_deliver_player_linkdead
 * Description: Hook that gets called to display that the messenger cannot
 *              deliver to someone who is LD
 * Arguments:   string who - the name of the recipient.
 */
public void
hook_cannot_deliver_player_linkdead(string who)
{
    write(this_object()->query_The_name(this_player()) 
        + " cannot deliver the message as "
        + capitalize(who) + " has vanished into the Void.\n");
}

/*
 * Function:    hook_cannot_deliver_wizard_busy
 * Description: Hook that gets called to display that the messenger cannot
 *              deliver to a wizard who has set the busy flag. Set a
 *              notify_fail() message.
 * Arguments:   object wizard - the object of the wizard who is busy
 */
public void
hook_cannot_deliver_wizard_busy(object wizard)
{
    notify_fail("That wizard does not want to be disturbed just now.\n");
}

/*
 * Function:    hook_send_message
 * Description: Hook that gets called to display the message of the
 *              messenger getting the message and leaving to deliver it
 */
public void
hook_send_message()
{
    write("You give your message to " + 
        this_object()->query_the_name(this_player()) +  ". It spreads " +
        "its wings and launches into the air, disappearing into the " +
        "distance.\n");
    say(QCTNAME(this_player()) + " gives a message to " + 
        QNAME(this_object()) + ". It spreads its " +
        "wings and launches into the air, disappearing into the " +
        "distance.\n");
}

/*
 * Function:    hook_resend_message
 * Description: Hook that gets called to display the message of the
 *              messenger being asked to re-deliver after a failed attempt.
 */
public void
hook_resend_message()
{
    write("You convince " + this_object()->query_the_name(this_player()) +
        " to try again. It spreads its wings and launches in to the " +
        "air, disappearing into the distance.\n");
    say(QCTNAME(this_player()) + " convinces " + QNAME(this_object())
        + " to try again. It spreads its wings and launches into the " +
        "air, disappearing into the distance.\n");
}

/*
 * Function:    hook_dismiss_messenger
 * Description: Hook that gets called to display the message when the
 *              player dismisses the messenger (to go home).
 */
public void
hook_dismiss_messenger()
{
    write("You dismiss " + this_object()->query_the_name(this_player()) + 
        ".\n");
    say(QCTNAME(this_player()) + " dismisses " + QTNAME(this_object()) + 
        ".\n");
}

/*
 * Function:    hook_deliver_message_failure
 * Description: Hook that gets called to display the message of the
 *              the messenger being unable to deliver the message and
 *              returning to the sender.
 * Arguments:   object sender - the person who sent the message
 */
public void
hook_deliver_message_failure(object sender)
{
    sender->catch_tell("Your " + this_object()->short() + " returns, " +
        "unable to find " + capitalize(gReceiver) + ".\n");
    tell_room(environment(sender), QCNAME(this_object()) + " flies down "
        + "onto the shoulder of " + QTNAME(sender) + ".\n", ({ sender }));   
}

/*
 * Function:    hook_deliver_message_success
 * Description: Hook that gets called to display the message of the
 *              messenger successfully delivering the message to the
 *              recipient.
 * Arguments:   object receiver - the person receiving the message
 */
public void
hook_deliver_message_success(object receiver)
{
    receiver->catch_msg(QCNAME(this_object()) + " lands on your shoulder "
        + "and gives you a message from " + capitalize(gSender) + ".\n");
    tell_room(environment(receiver), QCNAME(this_object()) + " lands on "
        + QTPNAME(receiver) + " shoulder and gives " +HIM_HER(receiver) + 
        " a message.\n", ({ receiver }));
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
    if (living(room = environment()))
    {
        room = environment(room);
    }
    tell_room(room, QCTNAME(this_object()) + " regally extends its " +
        "wings and soars up in to the air, flying back to its eyrie.\n");
}