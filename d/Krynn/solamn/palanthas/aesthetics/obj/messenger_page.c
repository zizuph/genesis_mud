/*
 * Based on carrier pigeon ~Krynn/solamn/vin/obj/pigeon.c
 * Credit to Tricky, Elessar, Nick, Olorin, and Aridor
 * for their work on that file.
 *
 * Page hired out as messenger in Aesthetics quarter of
 * Palanthas.
 *
 * Mortis 05.2006
 *
 */

#include "../../local.h"
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

#define VROOM		"/d/Krynn/solamn/vin/room/"

inherit CITIZEN;
inherit "/lib/messenger";

/* The home of the page. */
#define PAGE_HOME VROOM + "page_store"

/* The message. */
#define MESSAGE_OBJ MONKS + "obj/message"

/* The delay between sending the message and the receiving of it. */
#define SLOWLY random(6) + 25

/* The number of times the page will carry a message. 
 * #define TIMES 8
 *
 * Commented out by Mortis.  This is a good way to show at the
 * top that the # of times you can use the page is 8, but it is
 * a flawed way to operate the code if the long is based on TIMES'
 * value when TIMES never changes.
 */

/* Prototypes */
int return_to(object dest);
int run_to_someone(object dest);
void set_owner(object player);
void set_owner_initial();
int test_page_killer(object pl);
int my_gender();

string myadj = one_of_list(({"well-dressed", "aloof", "quiet", "restless",
			   "fidgety", "composed", "dashing", "bright-eyed", "fresh"}));
int gender = G_MALE;
object owner;

public void
create_messenger()
{
	// Set the message object for the messenger library
    set_message_object_file(MESSAGE_OBJ);
    set_number_of_uses(8);    
}

void
create_krynn_monster()
{
    seteuid(getuid(TO));

    // Initialize the messenger
    init_messenger();
    
	set_name("page");
	set_pname("pages");
    add_name("messenger");
	set_adj(({"young"}));
	add_adj(myadj);
	set_race_name("human");

	set_gender(my_gender());
	set_short("@@my_short");
	set_long("@@my_long@@");

	add_prop(OBJ_I_WEIGHT,  350);
	add_prop(CONT_I_WEIGHT, 350);
	add_prop(OBJ_I_VOLUME,  350);
	add_prop(CONT_I_VOLUME, 350);
	add_prop(OBJ_I_NO_GET, 0);
	add_prop(OBJ_I_NO_DROP, 0);
	add_prop(LIVE_I_NON_REMEMBER, 1);
	add_prop(NPC_M_NO_ACCEPT_GIVE, " doesn't seem interested in performing "
	+ "as your beast of burden.\n");

	set_alarm(0.1, 0.0, set_owner_initial);	
}

void
init_living()
{
    ::init_living();
	add_action("do_release","return",0);
}

int
my_gender()
{
	if (random(10) == 1)
		gender = G_FEMALE;

	return gender;
}

string
my_short()
{
	string mygender;

	if (gender == G_FEMALE)
		mygender = "female";
	else
		mygender = "male";

	return myadj + " young " + mygender + " page";
}

string
my_long()
{
	string ifreply = "";

	if (gNumSent < 8)
		ifreply = " or <send reply>";

	if (owner && owner == TP) 
		return "Dressed in white stockings and a tight, long-sleeved shirt, "
		+ "the page stands at the ready in a silver-trimmed white tunic "
		+ "bearing the white tower of Palanthas crossed by a feather above "
		+ "the center, the insignia of the Pages.  You have retained the "
		+ "services of this page for the purpose of sending messages to "
		+ "others via <send name>" + ifreply + ".  If the page fails to "
		+ "deliver the message, you may try again with <resend>.  You may "
		+ "<return page> if you no longer require page services.\n";

    if (owner && owner != TP)
		return "Dressed in white stockings and a tight, long-sleeved shirt, "
		+ "the page stands at the ready in a silver-trimmed white tunic "
		+ "bearing the white tower of Palanthas crossed by a feather above "
		+ "the center, the insignia of the Pages.  This page is in the "
		+ "employ of " + owner->query_name() + ", retained for the purpose "
		+ "of sending messages to others via <send name> or back to "
		+ HIM(owner) + " with <send reply>.  If the page fails to "
		+ "deliver your message, you may try again with <resend>.  "
		+ "You may also <return page> back to " + owner->query_name()
		+ ".\n";

    return "Dressed in white stockings and a tight, long-sleeved shirt, "
		+ "the page stands at the ready in a silver-trimmed white tunic "
		+ "bearing the white tower of Palanthas crossed by a feather above "
		+ "the center, the insignia of the Pages.  The services of pages "
		+ "are commonly used by those in need of <send>ing messages.\n";
}

int
do_release(string str)
{
	if (!str)
	{
		write("Release what?\n");
		return 1;
	}

	if (str == "page" || str == "young page" || str == myadj + " page" || str == myadj + " young page")
	{
		write("You release the page to return to its employer.\n");
		say(QCTNAME(TP) + " releases the page.\n");

		if (TP != owner) 
			return_to(owner);

		else 
			return_messenger_home();

		return 1;
	}

	return 0;
}

int
return_to(object dest)
{
	if (!dest) 
	{
		return_messenger_home();
		return 1;
	}

	set_alarm(4.0, 0.0, "run_to_someone", dest);

	if (living(E(TO)))
		tell_object(E(TO), "The page strains to hear a call in the distance.\n");

	else
		tell_room(E(TO), "The page strains to hear a call in the distance.\n");

	return 1;
}

int
run_to_someone(object dest)
{
	if (!dest) 
		tell_object(owner,"Bug - no dest.\n");

	if (living(E(TO)))
		tell_room(E(E(TO)), "The " + short() + " jogs away.\n");

    else 
		tell_room(E(TO), "The " + short() + " jogs away.\n");

	if(!dest)
	{
		remove_object();
		return 1;
	}

	TO->move(dest);

	tell_object(dest,"A " + short() + " jogs up to you and stands at the "
	+ "ready to provide service.\n");
	tell_room(E(dest), "A " + short() + " jogs up to " + QTNAME(dest)
	+ " and stands at the ready to provide service.\n", dest);

	test_page_killer(dest);

	return 1;
}

void
set_owner_initial()
{
	owner = E(TO);
	test_page_killer(owner);
}

void
set_owner(object player)
{
	if (!player)
		return;

	owner = player;
}

string
query_owner()
{
	string shit = owner->query_name();
	return "hi " + shit;
}

int
start_place()
{
    TO->move(PAGE_HOME);

	tell_room(E(TO), "A " + short() + " jogs in and stands at the ready.\n");
	set_alarm(15.0, 0.0, "return_to", owner);
	return 1;
}

int
test_page_killer(object pl)
{
	if (pl->query_prop("_player_is_page_killer") == 1) 
	{
		tell_object(pl,"The page recognizes you as a killer of pages, "
		+ "and hurriedly runs away screaming:  Hagen!  It's the page-"
		+ "killer!\n");

		tell_room(E(pl), "The page is scared by " + QTNAME(pl) + " and "
		+ "runs away screaming:  Hagen!  It's the page-killer!\n", pl);

		return_messenger_home();
	}

	return 1;
}

void
do_die(object killer)
{
	killer->add_prop("_player_is_page_killer", 1);
	::do_die(killer);
}

public void
hook_send_message()
{
	write("You hand your message to the page.\n");
	say(QCTNAME(TP) + " hands a message to " + HIS(TP) + " page.\n");
	tell_room(E(TO), "The " + short() + " jogs off to deliver a message.\n");	
}

public void
hook_resend_message()
{
	write("You instruct the page to make yet another try.\n");
	say(QCTNAME(TP) + " instructs " + HIS(TP) + " page to make yet "
	    + "try.\n");
	tell_room(E(TO), "The " + short() + " jogs off to deliver a message.\n");	
}

public void     
hook_deliver_message_failure(object sender)
{
	tell_object(sender, "Your " + short() + " returns unable to find "
	    + C(gReceiver) + ".\n");
	tell_room(E(sender), "A young page arrives jogging and hands "
		+ QTNAME(sender) + " a message.\n", sender);
}

public void     
hook_deliver_message_success(object receiver)
{
	tell_object(receiver, "A young page arrives jogging and hands you a "
    	+ "message from " + C(gSender) + ".\n");
	tell_room(E(receiver), "A young page arrives jogging and hands "
		+ QTNAME(receiver) + " a message.\n", receiver);
}

public void
hook_messenger_returns_home()
{
	object room;

	if (living(room = E(TO)))
		room = E(room);

	tell_room(room, "The " + short() + " jogs away.\n");
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
