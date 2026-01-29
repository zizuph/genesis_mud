/*
 * pigeon.c
 *
 * Used in nyreese/cadu_pig.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/*
*  Carrier pigeon.
*  This one can bring a message from one player to another. This will
*  (ofcourse) take a while. Maybe it's a compensation for the loss of
*  the 'tell' command.                                  Tricky, dec 1991
*
*  Added the idea of Elessar: a pigeon cannot take of from within a room,
*  i.e. it refuses to take off in a room that has the ROOM_I_INSIDE
*  property defined as != 0. Then the player can try to send it again
*  outside. Like always, wizards won't notice this.     Tricky, apr 1992
*/

#pragma save_binary
#pragma strict_types

inherit "/std/creature";
inherit "/std/combat/unarmed";

#include "defs.h"
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

/* The delay between sending the message and the receiving of it. */
#define SLOWLY random(20) + 30

/* The number of times the pigeon will carry a message. */
#define TIMES 2
#define UNKNOWN "unknown"

string gMessage, gWho, gSender, gLocation;
int gUsage;

void deliver();
void return_home();
void send_mail();

void
create_creature()
{
    set_name("pigeon");
    set_pname("pigeons");
    set_alignment(30); 
    set_race_name("pigeon");
    set_adj(({"black", "carrier"}));
    set_short("black carrier pigeon");
    set_pshort("black carrier pigeons");
    set_gender(1);
    set_long("This is your carrier pigeon. It sits comfortable on your " +
             "shoulder, waiting for you to write a message. You can write " +
             "someone by typing 'send <name>'" +
#if TIMES > 1
             " or 'send reply'" +
#endif
             ". If the pigeon fails to deliver the message you can tell it " +
             "to try again with the 'resend' command.\n");
    gUsage = 0;
    add_prop(OBJ_I_WEIGHT, 350);
    add_prop(CONT_I_WEIGHT, 350);
    add_prop(OBJ_I_VOLUME, 350);
    add_prop(CONT_I_VOLUME, 350);
    add_prop(OBJ_I_NO_GET, 0);
    add_prop(OBJ_I_NO_DROP, 0);
    add_prop(LIVE_I_NON_REMEMBER, 1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, " does not seem to be able to carry " +
	     "anything else but small messages.\n");

    set_attack_unarmed(1, 5, 5, W_IMPALE, 100, "beak");
    set_hitloc_unarmed(1, ({ 5, 7, 3}), 100, "body");
}

int
query_knight_prestige()
{
    return 2;
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
   
    who = lower_case(who);
   
    if (gUsage >= TIMES)
    {
      	write("The pigeon refuses to deliver another message.\n");
      	return 1;
    }

    if (environment(tp)->query_prop(ROOM_I_INSIDE))
    {
       	write("You can't send out the pigeon when you're not " +
		"out in open air.\n");
       	return 1;
    }

    if (who == "reply")
    {
        /* Has a message been written before? */
        if (!gUsage)
        {
            write("You are the first sender of a message. " +
                  "You cannot reply.\n");
            return 1;
        }
        who = gSender;
    }

    /* If a player knows the name of another player, let him send the pigeon. */
    gWho = who;
    gSender = lower_case(tp->query_name());

    if (!this_player()->query_met(gWho))
    {
        notify_fail("You do not remember being introduced to anyone named " +
                    capitalize(gWho) + ".\n");
        return 0;
    }

    target = find_player(gWho);
   
    /* It is useless to write a message to someone who isn't in the game. */
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

    say(QCTNAME(tp) + " starts to scribble some words on a note.\n");
    write("Enter your message.\n" +
          "On any line you can give ** to end, or ~q to abort the message.\n");
    gMessage = "";
    write("-->");
    input_to("write_more");
    return 1;
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
       gMessage = "";
       write("Message aborted.\n");
       return;
   }

   gMessage += (str + "\n");
   write("-->");
   input_to("write_more");
   return;
}

void
send_mail()
{
   object env;
   
   if (!gMessage || gMessage == "")
   {
       write("Message aborted.\n");
       return;
   }
   write("You give the message to the pigeon.\n");
   say(QCTNAME(this_player()) + " gives a message to " +
       this_player()->query_possessive() + " pigeon.\n");
   
   tell_room(environment(this_player()),
       "The black carrier pigeon flaps its wings and flies up to the sky.\n");
   
   /* Move the object to a temporary room */
   move(NYREESEDIR + "pig_tmp_room");
   set_alarm(itof(SLOWLY), 0.0, deliver);
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
	write("You convince the pigeon to make yet another try.\n");
        move(NYREESEDIR + "pig_tmp_room");
        set_alarm(itof(SLOWLY), 0.0, deliver);
	return 1;
    }

    notify_fail("The pigeon doesn't want to make another try.\n");
    return 0;
}

void
deliver()
{
    object target, message;
    /* Does our initial target still exist? */
    target = find_player(gWho);
    if (objectp(target) && (environment(target)->query_prop(ROOM_I_INSIDE)))
    {
        target = 0;
    }

    /* Does our sender still exist? */
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
       	tell_object(target, "Your black carrier pigeon returns, " +
                    "unable to find " + capitalize(gWho) + ". It lands on " +
                    "your shoulder and you retrieve your message.\n");
	return;
    }
    else
        tell_object(target,
                    "A black carrier pigeon descends from the sky, lands on your "
                    + "shoulder and gives you a message from "
                    + capitalize(gSender) + ".\n");
    tell_room(environment(target),
              "A pigeon lands on " + QTNAME(target) + "'s shoulder and gives "
              + target->query_objective() + " a message.\n", target);
    message = clone_object(ROKEDIR + "obj/message");
    message->set_message(gMessage);
    message->set_sender(gSender);
    message->move(target);
   
    gMessage = "";             /* Erase the message */
    gUsage++;
    if (gUsage >= TIMES)
        set_alarm(10.0, 0.0, return_home);
}

void
return_home()
{
    object room;
    if (living(room = environment()))
        room = environment(room);
   
    tell_room(room,
              "The black carrier pigeon flaps its wings and flies away.\n");
    remove_object();
}
