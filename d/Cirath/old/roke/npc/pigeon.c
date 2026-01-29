/*
 * pigeon.c
 * FIXA
 * Used in nyreese/cadu_XXXX.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
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

inherit "/std/monster";

#include "defs.h"
#include <stdproperties.h>
#include <macros.h>

/* The delay between sending the message and the receiving of it. */
#define SLOWLY random(20) + 30

/* The number of times the pigeon will carry a message. */
#define TIMES 2

string gMessage, gWho, gSender;
int gUsage;

void deliver();
void return_home();
void send_mail();

void
create_monster()
{
   set_name("pigeon");
   set_pname("pigeons");
   set_alignment(30); 
   set_race_name("pigeon");
   set_adj(({"black","carrier"}));
   set_short("black carrier pigeon");
   set_pshort("black carrier pigeons");
   set_gender(1);
   set_long(break_string(
         "This is your carrier pigeon. It sits comfortable on your shoulder, "
         + "waiting for you to write a message. You can write someone by "
         + "typing 'send someone'"
#if TIMES > 1
            + " or 'send reply'"
#endif
            + ".\n",70));
   gUsage = 0;
   add_prop(OBJ_I_WEIGHT,350);
   add_prop(CONT_I_WEIGHT,350);
   add_prop(OBJ_I_VOLUME,350);
   add_prop(CONT_I_VOLUME,350);
   add_prop(OBJ_I_NO_GET,0);
   add_prop(OBJ_I_NO_DROP,0);
   add_prop(LIVE_I_NON_REMEMBER,1);
}

int
query_knight_presige()
{
   return 2;
}

void
init_living()
{
   add_action("do_send","send");
}

int
do_send(string who)
{
   string *known;
   mapping intro, remem;
   object target, tp;
   
   if (!who || who == "")
      return 0;
   
   tp = this_player();
   if (tp != environment())
      return 0;
   
   who = lower_case(who);
   
   if (gUsage >= TIMES)
      {
      notify_fail("The pigeon refuses to deliver another message.\n");
      return 0;
   }
   
   /* Send the same message again */
   if (who == "again")
      {
      if (!gMessage || gMessage == "")
         {
         notify_fail("You have not entered a message yet. You cannot send it again.\n");
         return 0;
       }
      send_mail();
      return 1;
   }
   
   /* Send a reply */
   if (who == "reply")
      {
      /* Has a message been written before? */
      if (!gUsage)
         {
         notify_fail("You are the first sender of a message. You cannot reply.\n");
         return 0;
       }
      who = gSender;
   }
    // Only players don't know everyone
/*
   else if (!(tp->query_wiz_level()))
      {
      known = ({ });
      if (mappingp(intro = tp->query_introduced()))
         known += m_indexes(intro);
      if (mappingp(remem = tp->query_remembered()))
         known += m_indexes(remem);
      
    //  Check if the player knows the one he's about to write
         if (member_array(who,known) < 0)
         {
         notify_fail("You have not been introduced to anyone named "
               + capitalize(who) + ".\n");
         return 0;
        }
   }
*/
   gWho = who;
   gSender = lower_case(tp->query_name());
   target = find_player(gWho);
   
   /* It is useless to write a message to someone who isn't in the game. */
   if (!target)
      {
      notify_fail("There is no such player logged in!\n");
      return 0;
   }
   say(QCTNAME(tp) + " starts to scribble some words on a note.\n");
   write("Enter your message.\n"
      + "On any line you can give ** to end, or ~q to abort the message.\n");
   gMessage = "";
   write("-->");
   input_to("write_more");
   return 1;
}

int
write_more(string str)
{
   if (str == "**")
   {
       send_mail();
       return 1;
   }
   if (str == "~q")
   {
       gMessage = "";
       write("Message aborted.\n");
       return 1;
   }
   gMessage += (str + "\n");
   write("-->");
   input_to("write_more");
   return 1;
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
   say(QCTNAME(this_player()) + " gives a message to "
      + this_player()->query_possessive() + " pigeon.\n");
   
   /* Check if flying out is possible at all */
      if (!(this_player()->query_wiz_level()))
      {
      env = environment(this_player());
      
      /* The pigeon cannot ascend to the sky inside a room */
      if (env->query_prop(ROOM_I_INSIDE))
         {
         tell_room(env,
            "The pigeon flies towards the ceiling, but cannot get out of the room.\n"
            + "After several attempts it returns to its sender.\n");
         write("Find an open area and try \"send again\" there.\n");
         return;
     }
   }
   
   tell_room(environment(this_player()),
      "The black carrier pigeon flaps its wings and flies up to the sky.\n");
   
   /* Move the object to a temporary room */
   move(ROKEDIR + "tmp_room");
   set_alarm(itof(SLOWLY), 0.0, deliver);
   return;
}

void
deliver()
{
    object target, message;
    /* Does our initial target still exist? */
    target = find_player(gWho);
    if (!target || (environment(target)->query_prop(ROOM_I_INSIDE)))
    {
        /* Does our sender still exist? */
        target = find_player(gSender);
        if (!target)
        {
            remove_object();
            return;
        }
    }
    /* Go to the target */
    move(target);
    tell_object(target,break_string(
         "A black carrier pigeon descends from the sky, lands on your "
         + "shoulder and gives you a message from "
         + capitalize(gSender) + ".\n",70));
    tell_room(environment(target),
         "A pigeon lands on " + QCTNAME(target) + "'s shoulder and gives "
         + target->query_objective() + " a message.\n",target);
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
