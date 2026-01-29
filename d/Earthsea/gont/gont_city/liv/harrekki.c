/*****************************************************************
 * harrekki.c to substitute for carrier pigeon. Since it can both
 * fly and crawl, it can go anywhere in Genesis
 *
 * Based on :
 * 
 *  Carrier pigeon.
 *  This one can bring a message from one player to another. This will
 *  (ofcourse) take a while. Maybe it's a compensation for the loss of
 *  the 'tell' command.                                  Tricky, dec 1991
 *
 *  Slight modifications by Elessar, March 1992.
 *  Nick was here, May 1992. ** Keep on smiling **
 *  Nick again, March
 *  Mercade, September 14 1994. Removed certain confirmation of non-receipt.
 */

#pragma save_binary

inherit "/std/creature";
inherit "/std/combat/unarmed";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

/* The delay between sending the message and the receiving of it. */
#define SLOWLY random(20) + 30

/* The number of times the harrekki will carry a message. */
#define TIMES   3
#define UNKNOWN "unknown"
#define SUBLOC "_harrekki_subloc"


string gMessage, gWho, gSender, gLocation;
int gUsage;

void
create_creature()
{
    set_name("harrekki");
    set_pname("harrekkis");
    add_name("dragon");
    add_pname("dragons");
    set_adj(({"red", "green", "winged"}));
    add_adj("red-winged");
    set_race_name("harrekki");
    set_short("red-winged harrekki");
    set_pshort("red-winged harrekkis");
    set_long(
	"This tiny creature, no larger than your hand, is a miniature "+
	"version of its larger cousin, the dragon. Green and lizardlike, "+
	"it has sharp talons and red, webbed wings. Since it can both "+
	"fly and crawl, it can go to many far-away places to deliver "+
	"messages. "+
	"You can 'send <name>' "+
#if TIMES > 1
	"or 'send reply'. "+
#endif
	"If the harrekki fails to deliver the message, you can"+
	" try again with the 'resend' command.\n");

    gUsage = 0;
    add_prop(CONT_I_WEIGHT, 350);
    add_prop(CONT_I_VOLUME, 350);
    add_prop(OBJ_I_WEIGHT, 350);
    add_prop(OBJ_I_VOLUME, 350);
    add_prop(OBJ_I_NO_GET, 0);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(OBJ_I_NO_DROP, 0);
    add_prop(LIVE_I_NON_REMEMBER, 1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, " does not seem to be able to carry " +
      "anything else but small messages.\n");

    set_attack_unarmed(1, 5, 5, W_IMPALE, 100, "tiny talon");
    set_hitloc_unarmed(1, ({ 5, 7, 3}), 100, "body");
}

void
init_living()
{
    add_action("do_send", "send");
    add_action("resend", "resend");
}

int
do_send(string who)
{
    string known, intro, remem;
    object target, tp;

    if (!who || who == "")
	return 0;

    tp = this_player();
    if (tp != environment())
	return 0;

    if (gUsage >= TIMES)
    {
	write("The harekki refuses to deliver another message.\n");
	return 1;
    }


    if (who == "reply")
    {
	/* Has a message been written before? */
	if (!gUsage)
	{
	    write("You are the first sender of a message. "+
	      "You cannot reply.\n");
	    return 1;
	}
	who = gSender;
    }

    /* If a player knows the name of another player, let him send the pigeon.
*/
    gWho = who;
    gSender = lower_case(tp->query_name());

    if (!this_player()->query_met(gWho))
    {
	notify_fail("You do not remember being introduced to anyone named " +
	  capitalize(gWho) + ".\n");
	return 0;
    }

    /* It is useless to write a message to someone who isn't in the game. */
    target = find_player(gWho);
    if (!target)
    {
	write("There is no such player logged in!\n");
	return 1;
    }

    /* Save the location of the player. Only if s/he stays, there will be
     * confirmation.
     */
    if (objectp(environment(tp)))
    {
	gLocation = file_name(environment(tp));
    }
    else
    {
	gLocation = UNKNOWN;
    }

    write("Enter your message.\n"
      + "On any line you can give ** to end, or ~q to abort the message.\n");
    gMessage = "";
    write("-->");
    input_to("write_more");
    return 1;
}

void
send_mail()
{
    if (gMessage == "")
    {
	write("Message aborted.\n");
	return;
    }
    write("You give the message to the harrekki.\n");
    say(QCTNAME(this_player()) + " gives a message to " +
      this_player()->query_possessive() + " harrekki.\n");

    tell_room(environment(this_player()),
      capitalize(LANG_THESHORT(this_object())) +
      " flaps its webbed wings, screeches loudly "+
      "and flies away.\n");

    /* Move the object to a temporary room */
    move("/d/Earthsea/obj/harrekki_roost");
    set_alarm(itof(SLOWLY), 0.0, "deliver");
    return;
}

void
write_more(string str)
{
    if (str == "**")
    {
	send_mail();
	return;
    }

    if (str == "~q")
    {
	write("Message aborted.\n");
	return;
    }

    gMessage += (str + "\n");
    write("-->");
    input_to("write_more");
    return;
}

int
resend(string str)
{
    object target;

    if (!gSender || !gWho || this_player() != find_player(gSender))
    {
	notify_fail("You can't resend if you haven't sent first!\n");
	return 0;
    }

    if (target = find_player(gWho))
    {
	write("You convince the harrekki to make yet another try.\n");
	move("/d/Earthsea/obj/harrekki_roost");
	set_alarm(itof(SLOWLY), 0.0, "deliver");
	return 1;
    }

    notify_fail("The harrekki doesn't want to make another try.\n");
    return 0;
}

void
deliver()
{
    object target, message;

    // harrekki can go anywhere

    target = find_player(gWho);

    /* If the target is not found, the sender is tracked. If s/he moved, the
     * harrekki is not able to re-locate him/her.
     */
    if (!target)
    {
	target = find_player(gSender);
	if ((gLocation == UNKNOWN) ||
	  (objectp(target) && (file_name(environment(target)) != gLocation)))
	{
	    target = 0;
	}

	if (!objectp(target))
	{
	    remove_object();
	    return;
	}
    }

    /* Go to the target */
    move(target);
    if (target == find_player(gSender))
    {
	tell_object(target, "Your " +
	    this_object()->query_short() + " returns, "+
	    "unable to find " + capitalize(gWho) + ". It lands on " +
	    "your arm and you retrieve your message.\n");
	return;
    }
    else
	tell_object(target,
	    capitalize(LANG_ASHORT(this_object())) + " descends from "+
	    "above, sinks its talons into your arm, and gives "+
	    "you a message from "
	    + capitalize(gSender) + ".\n");

    tell_room(environment(target),
      capitalize(LANG_ASHORT(this_object())) + " lands on "+
      QCTNAME(target) + "'s arm and gives "
      + target->query_objective() + " a message.\n",target);


    target->add_subloc(SUBLOC, this_object());
    message = clone_object("/d/Genesis/obj/message");
    message->set_pshort("messages");
    message->set_pname("messages");
    message->set_message(gMessage);
    message->set_sender(gSender);
    message->move(target);
    gUsage++;
    if (gUsage >= TIMES)
	set_alarm(10.0, 0.0, "return_home");
}

void
return_home()
{
    object room;
    if (living(room = environment()))
	room = environment(room);
    tell_room(room,
      capitalize(LANG_THESHORT(this_object())) + " flaps its "+
      "webbed wings and flies away.\n");
    remove_object();
}







void
leave_env(object from, object to)
{
    ::leave_env(from, to);
    if (living(from))
	from->remove_subloc(SUBLOC);
}


string
show_subloc(string subloc, object carrier, object for_obj)
{
    object to = this_object();
    string str;

    if (carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	return "";



    if (carrier == to)
	return "";
    if (for_obj == carrier)
	str = "A small red-winged dragon rides on your arm.\n";
    else
	str = "A small red-winged dragon rides on "+
	carrier->query_possessive() + " arm.\n";

    return str;
}

