/*
 *  Carrier pigeon.
 *  This one can bring a message from one player to another. This will
 *  (ofcourse) take a while. Maybe it's a compensation for the loss of
 *  the 'tell' command.                                  Tricky, dec 1991
 *
 *  Slight modifications by Elessar, March 1992.
 *  Nick was here, May 1992. ** Keep on smiling **
 */

inherit "/std/creature";
inherit "/std/combat/unarmed";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

/* The delay between sending the message and the receiving of it. */
#define SLOWLY random(20) + 30

/* The number of times the pigeon will carry a message. */
#define TIMES 3

string gMessage, gWho, gSender;
int gUsage,pigeon_busy,times;
object owner;

create_creature()
{
   set_name("pigeon");
   set_pname("pigeons");
   set_race_name("pigeon");
   set_adj(({"white","carrier"}));
   set_short("white carrier pigeon");
   set_pshort("white carrier pigeons");
   set_long("@@long_func");
   gUsage = 0;
   add_prop(OBJ_I_WEIGHT,350);
   add_prop(OBJ_I_VOLUME,350);
   add_prop(OBJ_I_NO_GET,0);
   add_prop(OBJ_I_NO_DROP,0);
   add_prop(LIVE_I_NON_REMEMBER,1);
   set_times_to_fly();
   set_attack_unarmed(1, 5, 5, W_IMPALE, 100, "beak");
   set_hitloc_unarmed(1, ({ 5, 7, 3}), 100, "body");
}

init_living()
{
   add_action("do_send","send",0);
   add_action("do_return","return",0);
}

long_func()
{
  if (owner && owner == this_player()) 
    return "This is your personal carrier pigeon. You can send messages to\n"+
    "other players by typing 'send <player>'. If you want the pigeon back,\n"+
      "you can 'whistle for pigeon', and it will return, if it's still alive.\n";
  if (owner && owner != this_player())
    return "This is "+owner->query_cap_name()+"'s carrier pigeon. It is however a friendly\n"+
    "bird, and you might be able to send messages to others by 'send <player>'\n"+
      "or 'send reply'.\n";
  return "This is a white carrier pigeon, which you can use to send messages\n"+
    "to other players with 'send <player>'.\n";
}

do_send(string who)
{
   string known, intro, remem;
   object target, tp;

   if (!who || who == "")
      return 0;
   tp = this_player();
   if (tp != environment())
      return 0;
   if (gUsage >= times)
   {
      write("The pigeon refuses to deliver another message.\n");
      return 1;
   }
   if (environment(tp)->query_prop(ROOM_I_INSIDE))
     {
       write("You can't send out the pigeon when you're not out in open air.\n");
       return 1;
     }
   if (who == "reply")
   {
    /* Has a message been written before? */
      if (!gUsage)
      {
         write("You are the first sender of a message. You cannot reply.\n");
         return 1;
      }
      who = gSender;
   }
 /* If a player knows the name of another player, let him send the pigeon. */
   gWho = who;
   gSender = lower_case(tp->query_name());
   target = find_player(gWho);

 /* It is useless to write a message to someone who isn't in the game. */
   if (!target)
   {
      write("There is no such player logged in!\n");
      return 1;
   }
  pigeon_busy = 1;
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
   if (gMessage == "")
   {
      write("Message aborted.\n");
      return;
   }
   write("You give the message to the pigeon.\n");
   say(QCTNAME(this_player()) + " gives a message to "
    + this_player()->query_possessive() + " pigeon.\n");

   tell_room(environment(this_player()),
     "The white carrier pigeon flaps its wings and flies up to the sky.\n");
 /* Move the object to a temporary room */
   move("/d/Gondor/common/guild/pigeonroom");
   call_out("deliver", SLOWLY);
   return 1;
}

deliver()
{
   object target, message;
 /* Does our initial target still exist? */
   target = find_player(gWho);
   if (!target)
   {
    /* Does our sender still exist? */
      target = find_player(gSender);
      if (!target)
      {
      if (owner) { return_to(owner);
          return 1;
        }
         remove_object();
         return 1;
      }
   }
   else if (environment(target)->query_prop(ROOM_I_INSIDE))
     {
       target = find_player(gSender);
       if (!target)
	 {
      return_to(owner);
	   return 1;
	 }
     }

 /* Go to the target */
   move(target);
  pigeon_busy = 0;
   if (target == find_player(gSender))
       tell_object(target, break_string("Your white carrier pigeon returns, " +
		   "unable to find " + capitalize(gWho) + ". It lands on " +
	           "your shoulder and you retrieve your message.\n", 70));
   else
	tell_object(target, break_string(
      		"A white carrier pigeon descends from the sky, lands on your "
    		+ "shoulder and gives you a message from "
    		+ capitalize(gSender) + ".\n",70));

   tell_room(environment(target),
       "A pigeon lands on " + QCTNAME(target) + "'s shoulder and gives "
     + target->query_objective() + " a message.\n",target);

  message = clone_object("/d/Gondor/common/guild/obj/message");
   message->set_message(gMessage);
   message->set_sender(gSender);
   message->move(target);
   gUsage++;
   if (gUsage >= times)
      call_out("return_home",10);
}

do_return(str)
{
if (!str) {
    write("Return what?\n");
    return 1;
    }
  if (str == "pigeon" || str == "white pigeon" || str == "carrier pigeon") {
    write("You send the carrier pigeon up in the air again, to fly back home.\n");
    say(QCTNAME(this_player())+" sends the carrier pigeon away.\n",this_player());
    if (this_player()!=owner) fly_to_someone(owner);
    else return_home();
    return 1;
    }
  return 0;
}

query_busy()
{
  return pigeon_busy;
}

return_home()
{
   object room;
   if (living(room = environment()))
      room = environment(room);
   tell_room(room,
      "The white carrier pigeon flaps its wings and flies away.\n");
   remove_object();
}

return_to(object dest)
{
  if (!dest) {
    return_home();
    return 1;
  }
  pigeon_busy = 0;
  call_out("fly_to_someone",4,dest);
  if (living(environment(this_object())))
    {
      tell_object(environment(this_object()),"You hear a whistle from somewhere in the distance.\n");
    }
  else tell_room(environment(this_object()),"You hear a whistle from somewhere in the distance.\n");
  return 1;
}

fly_to_someone(dest)
{
if (!dest) tell_object(owner,"Bug - no dest.\n");
  if (living(environment(this_object())))
      tell_object(environment(this_object()),"The white pigeon flaps its wings and flies up in the sky!\n");
  else tell_room(environment(this_object()),"The white pigeon flaps its wings and flies up in the sky!\n");
  this_object()->move(dest);
  tell_object(dest,"A white pigeon comes flying, and lands on your shoulder.\n");
  tell_room(environment(dest),"A white pigeon comes flying, and lands on the shoulder of "+QTNAME(dest)+".\n",dest);
  return 1;
}

set_times_to_fly(int i)
{
if (!i) i = TIMES;
  if (i > 10) i = 10;
  times = i;
  return 1;
}

set_owner(object player)
{
  if (!player) return 0;
  owner = player;
  return 1;
}

start_place()
{
  this_object()->move("/d/Gondor/common/guild/pigeonroom");
  tell_room(environment(this_object()),"A white carrier pigeon comes flying, landing on the floor.\n");
  call_out("return_to",15,owner);
  return 1;
}


