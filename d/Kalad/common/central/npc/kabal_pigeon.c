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
* The pigeon has been altered to stop by the top of the monument
* instead of a temp_room. It can be killed there, and the message can be
* looted -> read by the killer. 
* Korat feb 1995
*/

inherit "/std/monster";

#include "/d/Kalad/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"


/* The delay between sending the message and the receiving of it. */
#define PAUSE itof(random(20)+30)

/* The number of times the pigeon will carry a message. */
#define TIMES 4

string gMessage, gWho, gSender;
int gUsage;
object cylinder, message;

void
create_monster()
{
   set_name("pigeon");
   set_pname("pigeons");
   set_alignment(30); 
   set_race_name("pigeon");
   set_adj(({"dirty","carrier"}));
   set_short("dirty carrier pigeon");
   set_pshort("dirty carrier pigeons");
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

query_knight_presige()
{
   return 2;
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
         notify_fail("You have not been introduced to anyone named "
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
   write("You put the message inside the cylinder attached to the pigeons leg.\n");
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
      "The dirty carrier pigeon flaps its wings and flies up to the sky.\n");
   
   /* Move the object to a temporary room */
   /* but first put the message inside a cylinder */
   cylinder = clone_object("/d/Kalad/common/central/obj/player_cylinder");
   message = clone_object("/d/Kalad/common/central/obj/player_message");
   message->set_message(gMessage);
   message->set_sender(gSender);
   message->move(cylinder);
   cylinder->change_prop(CONT_I_CLOSED, 1);
   cylinder->move(TO);
   move_living("M",CENTRAL(plaza/monument));
   tell_room(environment(TO),
      "A dirty pigeon lands on the bronze head, probably "+
      "to rest some before continuing its mission.\n");
   set_alarm(PAUSE,0.0,"deliver");
   return 1;
}

deliver() {
   object target;
   object *inv_pigeon;
   /* Does our initial target still exist? */
   target = find_player(gWho);
   if (!target || (environment(target)->query_prop(ROOM_I_INSIDE)))
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
   inv_pigeon= all_inventory(TO);
   if (sizeof(inv_pigeon) >0)
      {
      message->remove_object();
      cylinder->remove_object();
      tell_room(environment(TO),
         "The dirty pigeon flaps its wings and flies away.\n");
      move(target);
      tell_object(target,break_string(
            "A dirty carrier pigeon descends from the sky, lands on your "
            + "shoulder and gives you a message from "
            + capitalize(gSender) + ".\n",70));
      tell_room(environment(target),
         "A pigeon lands on " + QCTNAME(target) + "'s shoulder and gives "
         + target->query_objective() + " a message.\n",target);
      message = clone_object(CENTRAL(obj/player_message));
      message->set_message(gMessage);
      message->set_sender(gSender);
      message->move(target);
      
      gMessage = "";             /* Erase the message */
      gUsage++;
      if (gUsage >= TIMES)
         set_alarm(10.0,0.0,"return_home");
   }
   else
      {
      tell_room(environment(TO),
         "The dirty pigeon flaps its wings and flies away.\n");
      move(target);
      tell_object(target,
         "A dirty carrier pigeon descends from the sky, lands on your "
         +"shoulder. It carries no messages, something that strikes you as being odd.\n");
      tell_room(environment(target),
         "A pigeon lands on " + QCTNAME(target) + "'s shoulder.\n",target);
      gUsage++;
      if (gUsage >= TIMES)
         set_alarm(10.0,0.0,"return_home");
   }
}

return_home() {
   object room;
   if (living(room = environment()))
      room = environment(room);
   
   tell_room(room,
      "The dirty carrier pigeon flaps its wings and flies away.\n");
   remove_object();
}

