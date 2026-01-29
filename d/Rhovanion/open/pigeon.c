/*
 * Carrier pigeon by Milan.
 * Mabe by my favourite Cut&Paste method from
 * /d/Gondor/common/guild/obj/pigeon.c
 * /d/Rhovanion/common/npcs/post_rat.c
 */
/*
 *  Carrier pigeon.
 *  This one can bring a message from one player to another. This will
 *  (ofcourse) take a while. Maybe it's a compensation for the loss of
 *  the 'tell' command.                                  Tricky, dec 1991
 *
 *  Slight modifications by Elessar, March 1992.
 *  Nick was here, May 1992. ** Keep on smiling **
 *  added 'return' from /d/Genesis/obj/pigeon.c, Olorin, July 1993
 */

inherit "/std/creature";
inherit "/std/combat/unarmed";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Rhovanion/defs.h"

#define TEMP_ROOM   (MISTY_DIR + "gcaves/rat_room")
#define MESSAGE     (OBJ_DIR + "message")

string  gWho, gSender, gMessage = "";
object  owner;

string  gMessage, gWho, gSender;
object  owner;

void create_creature()
{
   set_name("pigeon");
   set_pname("pigeons");
   set_race_name("pigeon");
   set_adj(({"gray","carrier"}));
   set_short("gray carrier pigeon");
   set_pshort("gray carrier pigeons");
   set_long("@@long_func");

   add_prop(OBJ_I_WEIGHT,350);
   add_prop(CONT_I_WEIGHT,350);
   add_prop(OBJ_I_VOLUME,350);
   add_prop(CONT_I_VOLUME,350);
   add_prop(OBJ_I_NO_GET,0);
   add_prop(OBJ_I_NO_DROP,0);
   add_prop(LIVE_I_NON_REMEMBER,1);

   set_attack_unarmed(1, 5, 5, W_IMPALE, 100, "beak");

   set_hitloc_unarmed(0, ({ 5, 7, 3}), 30, "head");
   set_hitloc_unarmed(1, ({ 5, 7, 3}), 70, "body");
}

void init_living()
{
   add_action("do_send","send",0);
   add_action("do_return","return",0);
   add_action("do_resend","resend",0);
}

string long_func()
{
  if (owner && owner != TP) 
    return "This is "+owner->query_cap_name()+"'s nice gray carrier pigeon. "+
          "You can 'send reply' or 'resend pigeon'. You can also "+
          "'return pigeon' back home.\n";
  return "This is a nice gray pigeon. It has been trained to deliver "+
         "messages. You can send a messages to any player by typing "+
         "'send <player>' or 'resend pigeon'. You can also "+
          "'return pigeon' back home.\n";
}

int do_send(string who)
{
  object target;

  if (!who || who == "")
    return 0;
  if (TP != environment())
    return 0;
  
  if ((who != "reply") && owner && (TP != owner))
  {
    NF("You can only 'send reply' or 'resend pigeon'.\n");
    return 0;
  }
  if (who == "reply")
  {
    if(!owner)
    {
      NF("You are the first sender of a message. You cannot reply.\n");
      return 0;
    }
    who = gSender;
  }

  if (ENV(TP)->query_prop(ROOM_I_INSIDE))
  {
     NF("You can't send out the pigeon when you're not out in open air.\n");
     return 0;
  }

 /* If a player knows the name of another player, let him send the pigeon. */
   gSender = LOW(TP->query_real_name());
   gWho = LOW(who);
   target = find_player(gWho);

 /* It is useless to write a message to someone who isn't in the game. */
   if (!target)
   {
      NF("There is no '"+who+"' logged in!\n");
      return 0;
   }
   if(!owner) owner = TP;
   say(QCTNAME(TP)+" starts to write message.\n");
   write("Enter your message.\n"
       + "On any line you can give ** to end, or ~q to abort the message.\n");
   gMessage = "";
   write("-->");
   input_to("write_more");
   return 1;
}

int deliv_time(object ob1, object ob2)
{
  if(ENV(ob1) == ENV(ob2)) return random(10);
  if(explode(MASTER_OB(ENV(ob1)),"/")[2] ==
     explode(MASTER_OB(ENV(ob2)),"/")[2])
    return 10+random(10);
  return 20+random(20);
} 

int send_mail()
{
   if (gMessage == "")
   {
      NF("Message aborted.\n");
      return 0;
   }
   write("You give the message to the "+query_short()+".\n");
   say(QCTNAME(TP) + " gives a message to "
    + TP->query_possessive() + " "+query_short()+".\n");

   tell_room(environment(TP),
     "The "+query_short()+" flaps its wings and flies up to the sky.\n");
 /* Move the object to a temporary room */
   move(TEMP_ROOM);
   call_out("deliver", deliv_time(find_player(gWho),find_player(gSender)));
   return 1;
}

int write_more(string str)
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

int do_resend()
{
    object target;

    if (!gSender || !gWho || TP != find_player(gSender))
    {
	NF("You can't resend if you haven't sent first!\n");
	return 0;
    }

    if (target = find_player(gWho))
    {
      write("You convince the "+query_real_name()+" to make yet another try.\n");
      move(TEMP_ROOM);
      call_out("deliver", deliv_time(find_player(gWho),find_player(gSender)));
      return 1;
    }

    NF("The "+query_real_name()+" doesn't want to make another try.\n");
    return 0;
}

void return_home()
{
   object room;
   if (living(room = environment()))
      room = ENV(room);
   tell_room(room,
      "The "+query_short()+" flaps its wings and flies away.\n");
   remove_object();
}

int deliver()
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
         remove_object();
         return 1;
      }
   }
   else if (ENV(target)->query_prop(ROOM_I_INSIDE))
   {
      target = find_player(gSender);
      if (!target)
      {
         remove_object();
         return 1;
      }
   }

 /* Go to the target */
   move(target);
   if (target == find_player(gSender))
       tell_object(target, "Your "+query_short()+" returns, " +
		   "unable to find " + CAP(gWho) + ". It lands on " +
	           "your shoulder and you retrieve your message.\n");
   else
	tell_object(target, CAP(LANG_ADDART(query_short())) + 
                " descends from the sky, lands on your shoulder and gives "+
                "you a message from " + CAP(gSender) + ".\n");

   tell_room(ENV(target),
       "A "+query_real_name()+" lands on " + QCTNAME(target) + "'s shoulder and gives "
     + target->query_objective() + " a message.\n",target);

   message = clone_object(MESSAGE);
   message->set_message(gMessage);
   message->set_sender(gSender);
   message->move(target);

   if(target != find_player(gSender))
     gMessage = "";
   if ((target == owner) && (target != find_player(gSender)))
     call_out("return_home",2);
}

int do_return(string str)
{
  if (!str) 
  {
    NF("Return what?\n");
    return 0;
  }

  if (id(str))
  {
    write("You send the "+query_real_name()+" up in the air again, to fly back home.\n");
    say(QCTNAME(TP)+" sends the "+query_real_name()+" away.\n",TP);
      return_home();
    return 1;
  }
  return 0;
}

