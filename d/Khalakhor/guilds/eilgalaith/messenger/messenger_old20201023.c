/**********************************************************************
 * - messenger.c                                                    - *
 * - A Tiny Elven Nymph Dragon                                      - *
 * - original recoded by Damaris 2/2002                             - *
 * - replacement coded by Vitwitch 8/2020 to use new /lib/messenger - *
 **********************************************************************/


#define DRAGONPATH "/d/Khalakhor/guilds/eilgalaith/messenger/"
 
/*VW
#define DRAGONPATH "/w/vitwitch/nymphdr/newfix/"
 */

#include "/d/Khalakhor/guilds/eilgalaith/guild.h"

#include <files.h>
#include <language.h>
#include <stdproperties.h>
#include <macros.h>
#include <flags.h>
#include <const.h>

inherit "/std/messenger";  

// inherits /lib/messenger
/* following functions replace defaults in /lib/messenger */

// Global Variables
static int NSend = 0;
static int NoRepApp = 0;
static string  gSummoner = "";   /* The (lower case) summoner of the messenger. */

/*
 * Function:    do_send
 * Description: local mask of std function to control who can send.
 * Arguments:   who - the arguments to the send command. Valid ones
 *              are the name of the receiver, or "reply" to reply
 *              to a message that was received.
 * Returns:     0/1 - failure/success in sending
 */
public int 
do_send(string who)
{
    object target;
    object editor;

    string pSender;

    if (this_player() != environment())
    {
	return 0;
    }

    if (!strlen(who))
    {
        notify_fail("Send message to whom?\n");
    	return 0;
    }

    who = lower_case(who);

    if (who == "reply")
    {
        if (!strlen(gSender) || gSender == this_player()->query_real_name())
        {
           /* things got confused due to edit-abort 
              ... replies go to gSummoner anyway */
           gSender = gSummoner;
        }
        who = gSender;
    }
    else
    {
        if (NSend > 0)  
        {
            /* only gSummoner is allowed to send a new message */
            pSender = this_player()->query_real_name();
            if( !strlen(pSender) || (pSender != gSummoner) ) 
            {
                notify_fail("Only the nymph dragon summoner" +
                            " can send a fresh message.\n");
                return 0;
            }
        }
        else
        {
            gSummoner = this_player()->query_real_name();
            NSend = 1;
        }
    
    }

    /* Only deliver if they either know the person, or the setting is
     * set for whether the messenger can deliver to unmet individuals. */
    target = find_player(who);
    if (!query_can_deliver_unmet() && !this_player()->query_met(who) &&
        !target->query_prop(LIVE_I_ALWAYSKNOWN))
    {
        hook_cannot_deliver_unmet(who);
        return 0;
    }

    /* No target, or wizard is invisible. */
    if (!objectp(target) ||
        (target->query_wiz_level() && target->query_invis()))
    {
        hook_cannot_deliver_player_unavailable(who);
        return 0;
    }

    if (target->query_wiz_level())
    { 
        if (target->query_prop(WIZARD_I_BUSY_LEVEL) & BUSY_M)
        {
            hook_cannot_deliver_wizard_busy(target);
            return 0;
        }
    }

    if (target->query_linkdead())
    {
        hook_cannot_deliver_player_linkdead(who);
        return 1;
    }

    gSender = this_player()->query_real_name();
    gReceiver = who;

    say(QCTNAME(this_player()) + " starts to write a message.\n");
    this_player()->add_prop(LIVE_S_EXTRA_SHORT, " is writing a message");
    gMessage = "";

    setuid();
    seteuid(getuid());

    editor = clone_object(EDITOR_OBJECT);
    editor->set_activity("a message.");
    editor->edit("done_editing", "");

    return 1;
}

public void
create_messenger()
{
    // Customized options
    set_can_deliver_indoors(1);
    set_can_deliver_unmet(1);
    set_message_object_file(DRAGONPATH + "message");
    set_number_of_uses(0);

    set_gender(G_FEMALE);
    set_short("tiny elven nymph dragon");
    set_long("This is a tiny elven nymph dragon. She sits comfortably on "+
    "your shoulder, with her long tail tickling the side of your "+
    "neck, her wings outstretched, and her glittering eyes appraising you.\n" );

    /* 
     * true name of all tiny elven nymph dragons
     * only known by Wizards... no one gets to 'meet' her
     */
    set_name("galaithypix");

    set_race_name("dragon");
    set_adj(({"tiny", "elven", "dragon", "nymph"}));

    add_item(({"tail", "dragon tail", "nymph tail"}),
    "The tiny elven nymph dragon has a languid long tail, "+
    "which she enjoys tickling necks with.\n");

    add_item(({"wing", "dragon wings", "wings"}),
    "The tiny elven nymph dragon has wide wings, "+
    "of near transparency which split the light.\n");

    add_item(({"eyes", "dragon eyes", "eye"}),
    "The tiny elven nymph dragon has eyes whirling with, "+
    "bright colour that seem to see right through you.\n");

    set_appearance_offset(-150);
    add_prop(CONT_I_WEIGHT, 350);
    add_prop(CONT_I_VOLUME, 350);
    add_prop(LIVE_I_NON_REMEMBER, 1);

    add_prop(NPC_M_NO_ACCEPT_GIVE, " does not seem to be able "+
    "to carry anything but dragonscrolls.\n");

    add_prop(OBJ_M_NO_DROP, "She clings tightly by her long tail"
          + " coiled about you, while chittering nervously.\n"
          + " If you must, you can <dismiss> her homeward.\n");

    add_prop(OBJ_M_NO_GIVE, "She clings tightly by her long tail"
          + " coiled about you, while chittering nervously.\n");

    add_prop(OBJ_M_NO_ATTACK,
        "Adorably ignores your silly actions, shimmering in" +
        " and out of existence.\n");

 }
 

/*
 * Function name: appraise_messenger
 * Description  : Called when a person appraises the messenger. It gives
 *                information about the available commands. Note that if
 *                you do not inherit /std/messenger.c then you have to
 *                mask appraise_object() yourself and call this routine
 *                from it as described in the file header.
 * Arguments    : int num - the appraise semi-random number (unused here).
 */
public void
appraise_messenger(int num)
{
    if (NoRepApp==0)  
    {
        write("This " + this_object()->query_nonmet_name(this_player())
            + " can be used to <send> a new message from its summoner" 
            + " or to <send reply> from a recipient. <dismiss dragon>"
            + " will send her winging home to doze in a warm spot.\n");
       NoRepApp = 1;
    }
    else
       NoRepApp = 0;
}

public void
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_messenger(num);
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
    notify_fail("The nymph dragon chitters nervously --"+
                " a busy wizard is not to be disturbed!\n");
}

/*
 * Function:    hook_send_message
 * Description: Hook that gets called to display the message of the
 *              messenger getting the message and leaving to deliver it
 */
public void
hook_send_message()
{
    write("You give your dragonscroll to " + this_object()->query_the_name(this_player()) + ". "
        + capitalize(this_object()->query_pronoun()) + " takes wing and disappears "
        + "mysteriously into thin air.\n");
    say(QCTNAME(this_player()) + " gives a message to " + QTNAME(this_object())
        + ". " + capitalize(this_object()->query_pronoun()) + " takes wing and disappears "
        + "mysteriously into thin air.\n");
}

/*
 * Function:    hook_resend_message
 * Description: Hook that gets called to display the message of the
 *              messenger being asked to re-deliver after a failed attempt.
 */
public void
hook_resend_message()
{
    write("You cajole " + this_object()->query_the_name(this_player()) + " into trying again. "
        + capitalize(this_object()->query_pronoun()) + " takes wing and disappears "
        + "mysteriously into thin air.\n");

    say(QCTNAME(this_player()) + " convinces " + QTNAME(this_object()) + " to try again. "
        + capitalize(this_object()->query_pronoun()) + " takes wing and disappears "
        + "mysteriously into thin air.\n");
}

/*
 * Function:    hook_dismiss_messenger
 * Description: Hook that gets called to display the message when the
 *              player dismisses the messenger (to go home).
 */
public void
hook_dismiss_messenger()
{
    write("You whisper softly to the " + this_object()->query_the_name(this_player()) + 
          " and tell her she may return home.\n");

    say(QCTNAME(this_player()) + " whispers in thanks to " + QTNAME(this_object()) + ".\n");
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

    tell_room(room, QCTNAME(this_object()) + " takes her leave, takes wing" +
          " and mysteriously disappears.\n");

    say(QCTNAME(this_player()) + " sends " + QTNAME(this_object()) + " home.\n");
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
    receiver->catch_msg(QCTNAME(this_object()) + " mysteriously appears,"
        + " lands on your shoulder, tickling your neck with her tail"
        + " and you retrieve a dragonscroll from "
        + capitalize(gSender) + ".\n");

    tell_room(environment(receiver), QCTNAME(this_object())
        + " appears to land on the shoulder of "
        + QTNAME(receiver) + ".\n", ({ receiver }));
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
    sender->catch_tell("Your " + this_object()->short() + " returns, unable to find "
        + capitalize(gReceiver) + ".\n");
    tell_room(environment(sender), QCTNAME(this_object()) + " appears on the shoulder of "
        + QTNAME(sender) + ".\n", ({ sender }));
}

