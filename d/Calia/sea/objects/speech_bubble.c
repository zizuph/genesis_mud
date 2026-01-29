
/*
 *  Speech Bubble
 *  This bubble can bring a message from one player to another. This will
 *  (ofcourse) take a while. When it gets to the other player, the bubble
 *  will pop and the whole room will hear the message.
 *
 *  Based on the standard pigeon code in /d/Genesis/obj/pigeon.c
 *
 *  coder(s):   Jaacar
 *
 *  history:    17. 7.03    object coded                      Jaacar
 */

#pragma save_binary

inherit "/std/object";

#include <ss_types.h>
#include <cmdparse.h>
#include <composite.h>
#include <macros.h>
#include <flags.h>
#include <stdproperties.h>
#include "defs.h"

/* The delay between sending the message and the receiving of it. */
#define SLOWLY random(20) + 30

#define UNKNOWN "unknown"

string gMessage, gWho, gSender, gLocation;
int gUsage;

void
create_object()
{
    set_name("bubble");
    set_pname("bubbles");
    set_adj(({"small","magical"}));
    set_short("small magical bubble");
    set_pshort("small magical bubbles");
    set_long("This is a small magical bubble. You can speak into the "+
    	"bubble and have it take the message to someone far away. "+
        "You can do this by typing 'send <name>'."+
        "If the bubble fails to deliver the message, it will float "+
        "back to you and you can have it try again with the "+
        "'resend' command.\n");
    add_prop(CONT_I_WEIGHT, 5);
    add_prop(CONT_I_VOLUME, 5);
    add_prop(OBJ_I_NO_GET, 0);
    add_prop(OBJ_I_NO_DROP, 0);
    add_prop(NPC_M_NO_ACCEPT_GIVE, " does not seem to be able to carry " +
	     "anything else but small messages.\n");
}

void
init()
{
    ::init();
    add_action("do_send", "send");
    add_action("resend", "resend");
}

int
do_send(string who)
{
    string known, intro, remem;
    object target;

    if (!who || who == "")
      	return 0;

    if (TP != environment())
      	return 0;

    /* If a player knows the name of another player, let him send the pigeon. */
    gWho = who;
    gSender = lower_case(TP->query_name());

    if (gSender == who)
    {
        NF("You can't send the bubble to yourself!\n");
        return 0;
    }

    if (!TP->query_met(gWho))
    {
        NF("You do not remember being introduced to anyone named " +
            capitalize(gWho) + ".\n");
        return 0;
    }

    /* It is useless to write a message to someone who isn't in the game. */
    target = find_player(gWho);
    if (!target)
    {
      	write("There is no such person in the realms!\n");
      	return 1;
    }

    /* Save the location of the player. Only if s/he stays, there will be
     * confirmation.
     */
    if (objectp(environment(TP)))
    {
	gLocation = file_name(environment(TP));
    }
    else
    {
	gLocation = UNKNOWN;
    }

    write("Enter your message.\nOn any line you can give "+
        "** to end, or ~q to abort the message.\n");
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
    write("You speak your message into the small magical bubble.\n");
    say(QCTNAME(TP) + " speaks into " +
	TP->query_possessive() + " small magical bubble.\n");

    tell_room(environment(TP),
     	"The small magical bubble floats up and away until you can "+
        "no longer see it.\n");

 /* Move the object to a temporary room */
    move("/d/Krynn/common/void");
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

    if (!gSender || !gWho || TP != find_player(gSender))
    {
	NF("You can't resend if you haven't sent first!\n");
	return 0;
    }

    if (target = find_player(gWho))
    {
	write("You send the small magical bubble off for another try.\n");
	move("/d/Krynn/common/void");
	set_alarm(itof(SLOWLY), 0.0, "deliver");
	return 1;
    }

    NF("The bubble refuses to carry any more messages.\n");
    return 0;
}

void
deliver()
{
    object target, message;

    target = find_player(gWho);

/* If the target is not found, the sender is tracked. If s/he moved, the
 * bubble is not able to re-locate him/her.
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

    if (target->query_wiz_level())
    {
        if ((target->query_wiz_prop(WIZARD_I_BUSY_LEVEL) & BUSY_M) ||
            target->query_invis())
        {
            target = find_player(gSender);
        }
    }

 /* Go to the target */
    move(target);
    if (target == find_player(gSender))
    {
       	tell_object(target,"Your small magical bubble returns, " +
		   "unable to find " + capitalize(gWho) + ".\n");
	    return;
    }

    else if (environment(target)->query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER)
    {
        tell_object(target,"A small white bubble descends from above, "+
            "landing next to your ear.\nSuddenly the bubble pops.\n");

        tell_room(environment(target),"A small white bubble descends "+
            "from above and lands next to " + QCTNAME(target) + "'s ear, "+
            "popping as it does so.\n",target);

        tell_object(target,"As the bubble pops you hear "+
            "the voice of "+capitalize(gSender)+
            " saying:\n"+gMessage+"\n");
        remove_object();   
    }
    else if (environment(target)->query_prop(ROOM_I_TYPE) != ROOM_UNDER_WATER)
    {
        tell_object(target,"A small white bubble descends from above, "+
            "landing on your hand.\nSuddenly the bubble pops.\n");

        tell_room(environment(target),"A small white bubble descends "+
            "from above and lands on " + QCTNAME(target) + "'s hand, "+
            "popping as it does so.\n",target);

        tell_room(environment(target),"As the bubble pops you hear "+
            "the voice of "+capitalize(gSender)+
            " saying:\n"+gMessage+"\n\n");
        remove_object();
    }

}



