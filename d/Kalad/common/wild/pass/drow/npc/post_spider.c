/*
 * Post rat by Milan. 9.3.94.
 * Time of delivery depends slightly on distance (domains check)
 * It is of course longer than pigeon times...
 * But rats have advantage that they go indoor, can swim well and
 * generally there is almost NO place that rat cant get in.
 *  
 * All this is modification of Gondor pigeon.
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
 * 
 *  Added: #pragma strict_types
 *        add_name("messenger");
 *  Damaris 6/2003
 */
#pragma strict_types

inherit "/std/creature";
inherit "/std/combat/unarmed";

#include "/d/Kalad/defs.h"
#include <wa_types.h>
#include <std.h>

#define TEMP_ROOM "/d/Kalad/common/wild/pass/drow/spider_room"
#define MESSAGE "/d/Kalad/common/wild/pass/drow/obj/message"

string  gWho, gSender, gMessage = "";
object  owner;
int time_alarm;

void create_creature()
{
   set_name("spider");
   set_pname("spiders");
   add_name("messenger");
   set_race_name("spider");
   set_adj(({"small","black"}));
   set_short("small black spider");
   set_pshort("small black spiders");
   set_long("This is a small black spider. It has been trained by the Drow "+
      "to deliver messages. You can send a message to any player by typing "+
      "'send <player>'. If you want to send it back home just drop it.\n");

   add_prop(OBJ_I_WEIGHT,350);
   add_prop(CONT_I_WEIGHT,350);
   add_prop(OBJ_I_VOLUME,350);
   add_prop(CONT_I_VOLUME,350);
   remove_prop(OBJ_I_NO_GET);
   remove_prop(OBJ_I_NO_DROP);
   add_prop(LIVE_I_NON_REMEMBER,1);

   set_attack_unarmed(0, 5, 5, W_IMPALE, 30, "fangs");
   set_attack_unarmed(1, 5, 5, W_IMPALE, 35, "left forecep");
   set_attack_unarmed(2, 5, 5, W_IMPALE, 35, "right forecep");

   set_hitloc_unarmed(0, ({ 5, 7, 3}), 30, "head");
   set_hitloc_unarmed(1, ({ 5, 7, 3}), 60, "body");
   set_hitloc_unarmed(2, ({ 5, 7, 3}), 10, "legs");
}

void init_living()
{
   add_action("do_send","send",0);
}

int do_send(string who)
{
   if (!who || who == "")
      return 0;
   if (TP != environment())
      return 0;

   if (who == "reply")
   {
      if(!owner)
      {
         NF("You are the first sender of a message. You cannot reply.\n");
         return 0;
      }
      who = gSender;
   }

    gWho = who;
    gSender = lower_case(TP->query_name());

   // Replaced check if player is logged in by
   // check if player exists, Fysix, 25 Dec 1997
   if (!SECURITY->exist_player(who))
   {
      NF("Send to whom?\n");
      return 0;
   }

   if(!owner)
      owner = TP;

   say(QCTNAME(TP)+" starts to write a message.\n");
   write("Enter your message.\n"
       + "On any line you can give ** to end, or ~q to abort the message.\n");
   gMessage = "";
   write("-->");
   input_to("write_more");
   return 1;
}

float deliv_time(object ob1, object ob2)
{
    if(!objectp(ob1) || !objectp(ob2)) // no reciever? hmm
        return 10.0;
if(environment(ob1) == environment(ob2)) return itof(random(10));
if(explode(MASTER_OB(environment(ob1)),"/")[2] ==
explode(MASTER_OB(environment(ob2)),"/")[2])
    return itof(60+random(30));
  return itof(120+random(60));
} 

int send_mail()
{
   if (gMessage == "")
   {
      NF("Message aborted.\n");
      return 0;
   }
   write("You give the message to the "+query_short()+", and it "+
   "clamps it in its mouth.\n");
   say(QCTNAME(TP)+" gives a message to "+
       TP->query_possessive()+" "+query_short()+".\n");

   tell_room(environment(TP),"The "+query_short()+" skitters rapidly away.\n");

  /* Move the object to a temporary room */
   move(TEMP_ROOM);
   set_alarm(deliv_time(find_player(gWho),find_player(gSender)),0.0,"deliver",find_player(gSender));   
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
      gMessage = "";
      return 1;
   }
   gMessage += (str + "\n");
   write("-->");
   input_to("write_more");
   return 1;
}

void return_home()
{
   object room;
   if (living(room = environment()))
      room = environment(room);
   tell_room(room,"The "+query_short()+" skitters away.\n");
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
 /* Go to the target */
   move(target);
   if (target == find_player(gSender))
     tell_object(target, "Your "+query_short()+" returns, "+
        "unable to find "+capitalize(gWho)+". It gives you " +
	"back your message.\n");
   else
      tell_object(target, capitalize(LANG_ADDART(query_short()))+" skitters to you "+
         "and gives you a message from "+capitalize(gSender)+".\n");

   tell_room(environment(target),
      "A "+query_short()+" skitters to "+QTNAME(target)+" and gives "+
       target->query_objective()+" a message.\n",target);

   seteuid(getuid());
   message = clone_object(MESSAGE);
   message->set_message(gMessage);
   message->set_sender(gSender);
   message->move(target);

/* this snake will leave after delivering the message */
   if (target == owner)
      set_alarm(itof(random(10)),0.0,"return_home");
   else gMessage = "";
}

void 
enter_env(object dest, object old)
{
  ::enter_env(dest, old);
  if((gMessage == "") && (dest->query_prop(ROOM_I_IS)))
    set_alarm(itof(random(10)),0.0,"return_home"); 
}     
