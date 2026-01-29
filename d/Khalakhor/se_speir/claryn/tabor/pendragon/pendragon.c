
/* Pendragons are familiars to Librarians
 * which issue ink from their foremost wing
 * tip bones... which allow them to tattoo
 * cursive runes on the bodies of Librarians.
 * Vitwitch 09/2020
 */

#pragma save_binary
#pragma strict_types

inherit "/std/messenger";
/* inherits /lib/messenger
 following functions replace defaults in /lib/messenger */

// Global Variables
static int NoRepApp = 0;

#include <files.h>
#include <language.h>
#include <stdproperties.h>
#include <macros.h>
#include <flags.h>
#include <const.h>

/*VW
#define PENDRAGON_PATH "/w/vitwitch/pendragon/local/"
*/
#define PENDRAGON_PATH "/d/Khalakhor/se_speir/claryn/tabor/pendragon/"

/* do not change name nor adjective
   they are used for identification */
#define PENDRAGON_NAME "pendragon"
#define PENDRAGON_ADJ "inky"

#define PENDRAGON_WRIT "pendragon_tattoo"
#define PENDRAGON_MESSAGE "pendragon_inkblot"

#define INK_MAX_WRITING 80

// Global Variables
string librarian_name = "";
string ink_colour = "";


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

        pSender = this_player()->query_real_name();
        if( !strlen(pSender) || (pSender != librarian_name) ) 
        {
            notify_fail("Only the pendragon summoner" +
                        " can send a message.\n");
            return 0;
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
    /* messenger is a secondary role
       to librarian's companion
       and personal tattoo artist */

    // Customized options
    set_can_deliver_indoors(1);
    set_can_deliver_unmet(1);
    set_number_of_uses(1);  // will go and not come back 
    set_message_object_file(PENDRAGON_PATH + PENDRAGON_MESSAGE);

    set_gender(G_FEMALE);

    set_name(PENDRAGON_NAME);
    set_adj(({PENDRAGON_ADJ}));

    set_pname("pendragons");
    add_name("pendragon");
    add_name("dragon");

    set_race_name("dragon");

    set_short("pendragon");

    set_long(" This pendragon is imprinted on you."+
    " She sits comfortably on"+
    " your shoulder, with her tufted tail tickling your"+
    " neck and her appraising eyes awhirl with shifting"+
    " colours. Her outstretched wings drip ink in"+
    " anticipation of making a <dragon_tattoo>."+
    " She will also carry a message for you.\n");

    add_item(({"tail", "dragon tail", "tufted tail"}),
    " The pendragon has a long tail,"+
    " tufted in ink-stained blotter feathers.\n");

    add_item(({"wing", "dragon wings", "wings", "wingtips", "wingtip"}),
    " The pendragon has delicate wings webbed"+
    " between long scaly fingers. The sharp tips of these fingers drip with"+
    " ink. They twitch in anticipation of giving you a <dragon_tattoo> --" +
    " using your sage words in her distinctive ink...\n"+
    "... which can be scoured if you make a mistake.\n");

    add_item(({"eyes", "dragon eyes", "eye"}),
    "The pendragon has eyes whirling with "+
    "myriad colour, excited by the smooth expanse of your skin,"+
    " on which she can practice her <dragon_tattoo>s.\n");

    set_appearance_offset(-150);
    add_prop(OBJ_I_WEIGHT, 350);
    add_prop(OBJ_I_VOLUME, 350);
    add_prop(LIVE_I_NON_REMEMBER, 1);

    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_act_time(10);
    add_act("emote chitters contentedly from your shoulder.\n",1); 
    add_act("emote cleans excess ink from her wingtips.\n",1); 
    add_act("emote resettles her feathered tail, tickling your neck.\n",1);
    add_act("emote peers about for a colourful snack.\n",1);

    this_object()->add_prop(OBJ_M_NO_ATTACK,
        "You are reminded that the pen is mightier than the sword!\n");

    add_prop(NPC_M_NO_ACCEPT_GIVE, " does not accept "+
        "gifts nor treats, to <dragon_tattoo> is its own reward.\n");

    add_prop(OBJ_M_NO_DROP, "The pendragon clings tightly"+
          " -- her tailed coiled about you!\n"
          + " You can <dismiss> her if you must.\n");

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
        write("A " + this_object()->query_nonmet_name(this_player())
            + " is used by Keepers of Written Words to"
            + " <dragon_tattoo> their own words upon their own flesh." 
            + " They can also be used to <send> one-way messages to just"
            + " about anyone.  <dismiss dragon> will send her home."
            + " Whenever she takes wing and flies off, she"
            + " is prone to spend the rest of the day searching out"
            + " colourful snacks to keep her distinctive ink flowing."
            + " You must <summon> her back with one of her tattoos"
            + " if you wish her to attend you again.\n");
       NoRepApp = 1;
    }
    else
       NoRepApp = 0;
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
    notify_fail("The pendragon chitters nervously --"+
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
    write("You give a message to " + this_object()->query_the_name(this_player()) + ". "
        + capitalize(this_object()->query_pronoun()) + " eats the message, takes wing and disappears "
        + "in a cloud of " + ink_colour + " ink droplets.  She will not return unless you <summon> her again.\n");
    say(QCTNAME(this_player()) + " gives a message to " + QNAME(this_object())
        + ". " + capitalize(this_object()->query_pronoun()) + " eats the message, takes wing and disappears "
        + "in cloud of ink droplets.\n");
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
        + "in a cloud of ink droplets.\n");

    say(QCTNAME(this_player()) + " convinces " + QNAME(this_object()) + " to try again. "
        + capitalize(this_object()->query_pronoun()) + " takes wing and disappears "
        + "in a cloud of ink droplets.\n");
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
    receiver->catch_msg("A pendragon swoops down out"
        + " of thin air in a violent cloud-burst of " + ink_colour + " ink droplets."
        + " Ink spatters all over you just as the pendragon vanishes. Can"
        + " you interpret the inkblot?\n\n");

    tell_room(environment(receiver),
        "A pendragon swoops down out of nowhere, staining "
        + QTNAME(receiver) + " with an inkblot, before vanishing again.\n", 
         ({ receiver }));
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
    tell_room(environment(sender), QCNAME(this_object()) + " appears on the shoulder of "
        + QTNAME(sender) + ".\n", ({ sender }));
}


public void
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_messenger(num);
}


int
assign_ink_colour(string name)
{
    ink_colour = name;
    return 1;
}


int
assign_librarian_name(string name)
{
    librarian_name = name;
    return 1;
}

int
dragon_tattoo(string str)
{

    object writing_obj;

    object here = this_player();

    if ( !librarian_name 
         || (this_player()->query_real_name() != librarian_name) )
    {
        write("The pendragon regards you as a stranger, "+
          "she abruptly escapes your grasp, "+
          "wings beating up a cloud of fine ink drops "+
          "and disappears into empty space.\n");
        say(QCTNAME(this_player())+" is left behind by a pendragon, that "+
           "disappears in a cloud of ink droplets.\n");
        destruct();
     
        return 1;
    }

    notify_fail("What was that?\n");
    if (environment(this_object()) != this_player()) return 0;

    notify_fail("It is too dark to see.\n");
    if (!CAN_SEE_IN_ROOM(this_player())) return 0;

    notify_fail("What would you have <dragon_tattoo>'d on you?\n");
    if (!str) return 0;

    notify_fail("The pendragon is not able to tattoo you.\n"
         +" She keens in frustration.\n");
    if (!here) return 0;
 
    notify_fail("You don't have enough skin for such a big piece!\n"
      + " Grow more or tattoo less!\n");
    if (strlen(str) > INK_MAX_WRITING) return 0;

    setuid();
    seteuid(getuid(here));

    writing_obj = clone_object(PENDRAGON_PATH + PENDRAGON_WRIT);
    writing_obj->set_writing_data(ink_colour,str);

    this_object()->move(here, 1);
    writing_obj->move(here,1);

    this_player()->catch_msg("The sharpened wingtips of a"+
      " pendragon jab to and fro through your skin,"+
      " carving out elegant cursive runes, leaving your" +
      " body illuminated in distinctive " + ink_colour +
      " ink.\n");

    return 1;

}

public void
hook_dismiss_messenger()
{
    write("You dismiss a pendragon from your presence."+
          " She launches into the air," +
          " her wings shedding a cloud of " + ink_colour + " ink drops"+
          " before she vanishes."+
          " Through her tattoos upon your flesh,"+
          " you may <summon> her to you again.\n");
    say(QCTNAME(this_player()) + " dismisses a pendragon."+
          " She launches into the air," +
          " her wings shedding a cloud of ink drops"+
          " before she vanishes.\n");
}

public void
hook_messenger_returns_home()
{
    say("\n"); 
    write("\n");
}

void
init_living()
{
    ::init_living();
    add_action("dragon_tattoo","dragon_tattoo");
}

