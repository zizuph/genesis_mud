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
 *
 *  1996/06/07 Last modified
 *  2011/07/14 Lavellan, changed to creature, gave sensible hitlocs, and made
 *      it fly away when attacked anyway. Also improved description.
 *      TODO: convert to /std/messenger
 */

#pragma save_binary

//inherit "/std/monster";
inherit "/std/creature";

#include "defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/wa_types.h" // for hitlocs, just in case

/* The delay between sending the message and the receiving of it. */
#define SLOWLY random(20) + 30

/* The number of times the pigeon will carry a message. */
#define TIMES 2

string gMessage, gWho, gSender;
int gUsage;

deliver();
return_home();
public void attacked_by(object attacker);
public void cr_configure();

create_creature()
{
   set_name("bird");
   set_pname("pigeons");
   set_race_name("pigeon");
   set_adj(({"white","carrier"}));
   set_short("white carrier pigeon");
   set_pshort("white carrier pigeons");
   //set_long(break_string(
   set_long(
      //"This is your carrier pigeon. It sits comfortable on your shoulder, "
      "This is a carrier pigeon. It can sit comfortably on your shoulder, "
    //+ "waiting for you to write a message. You can write someone by "
    + "waiting for you to write a message. You can write to someone by "
    + "typing 'send someone'"
#if TIMES > 1
    + " or 'send reply'"
#endif
    //+ ".\n",70));
    + ".\n",70);
   gUsage = 0;
   add_prop(OBJ_I_WEIGHT,350);
   add_prop(CONT_I_WEIGHT,350);
   add_prop(OBJ_I_VOLUME,350);
   add_prop(CONT_I_VOLUME,350);
   add_prop(OBJ_I_NO_GET,0);
   add_prop(OBJ_I_NO_DROP,0);
   add_prop(NPC_M_NO_ACCEPT_GIVE, 1);
   add_prop(LIVE_I_NON_REMEMBER,1);
}

init_living()
{
   add_action("do_send","send",0);
}

do_send(who)
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
   /* Only players don't know everyone */
   else if (!(tp->query_wiz_level()))
   {
      known = ({ });
      if (mappingp(intro = tp->query_introduced()))
         known += m_indexes(intro);
      if (mappingp(remem = tp->query_remembered()))
         known += m_indexes(remem);

      /* Check if the player knows the one he's about to write */
      if (member_array(who,known) < 0)
      {
         notify_fail("You don't havenot been introduced to anyone named "
                    + capitalize(who) + ".\n");
         return 0;
      }
   }
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

write_more(str)
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
          return 1;
      }
   }

   tell_room(environment(this_player()),
     "The white carrier pigeon flaps its wings and flies up to the sky.\n");

   /* Move the object to a temporary room */
   move(STAND_DIR + "tmp_room");
   set_alarm(itof(SLOWLY), 0.0, deliver);
   return 1;
}

deliver() {
   object target, message;
 /* Does our initial target still exist? */
   target = find_player(gWho);
   if (!target)
   {
    /* Does our sender still exist? */
      target = find_player(gSender);
      if (!target)
      {
         remove_object();
         return 1;
      }
   }
   /* Go to the target */
   move(target);
   tell_object(target,break_string(
      "A white carrier pigeon descends from the sky, lands on your "
    + "shoulder and gives you a message from "
    + capitalize(gSender) + ".\n",70));
   tell_room(environment(target),
       "A pigeon lands on " + QCTNAME(target) + "'s shoulder and gives "
     + target->query_objective() + " a message.\n",target);
   message = clone_object(STAND_DIR + "message");
   message->set_message(gMessage);
   message->set_sender(gSender);
   message->move(target);

   gMessage = "";             /* Erase the message */
   gUsage++;
   if (gUsage >= TIMES)
      set_alarm(10.0, 0.0, return_home);
}

return_home() {
   object room;
   if (living(room = environment()))
      room = environment(room);
   tell_room(room,
      "The white carrier pigeon flaps its wings and flies away.\n");
   remove_object();
}

public void
attacked_by(object attacker)
{
    set_alarm(0.5, 0.0, return_home);
}

public void
cr_configure()
{
   add_hitloc(0, 80, "body", A_BODY);
   add_hitloc(0, 20, "head", A_HEAD);
}