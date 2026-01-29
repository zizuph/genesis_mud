/**********************************************************************
 * - snake.c                                                        - *
 * -                                                                - *
 * - Created by Damaris@Genesis 3/2004                              - *
 **********************************************************************/

#pragma strict_types
inherit "/std/creature";
inherit "/std/combat/unarmed";

#include "../guild.h"
#include <const.h>
#include <files.h>
#include <filter_funs.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#define TEMP_ROOM ROOM + "snake_pit"
#define MESSAGE MESSENGER_DIR + "message"
#define SNAKE_TIME 300.0



string  gWho, gSender, gMessage = "";
object  owner;
int time_alarm;

void
create_creature()
{
   set_name("snake");
   set_race_name("snake");
   set_adj(({"small","black"}));
   set_short("small black snake");
   set_long("This small black snake stares at you with tiny red eyes. It "+
      "coils around your arm, patiently waiting for you to command it. "+
      "You can command it to send with 'send <name>'\n");
   add_prop(OBJ_I_WEIGHT,550);
   add_prop(CONT_I_WEIGHT,550);
   add_prop(OBJ_I_VOLUME,550);
   add_prop(CONT_I_VOLUME,550);
   remove_prop(OBJ_I_NO_GET);
   remove_prop(OBJ_I_NO_DROP);
   add_prop(LIVE_I_NON_REMEMBER,1);
   
   set_attack_unarmed(0, 5, 5, W_IMPALE, 30, "fangs");
   
   set_hitloc_unarmed(0, ({ 5, 7, 3}), 30, "head");
   set_hitloc_unarmed(1, ({ 5, 7, 3}), 70, "body");
   
}

void init_living()
{
   add_action("do_send","send",0);
   /* this snake is magically summoned and will vanish unless it is used */
   time_alarm=set_alarm(SNAKE_TIME,0.0,"return_home");
}

int do_send(string who)
{
   object target;
   
   if (!who || who == "")
      return 0;
   if (TP != environment())
      return 0;
   /* If a player knows the name of another player, let him send the pigeon. */
   gSender = lower_case(TP->query_real_name());
   gWho = lower_case(who);
   target = find_player(gWho);
   
   /* It is useless to write a message to someone who isn't in the game. */
   if (!target)
      {
      NF("There is no '"+who+"' logged in!\n");
      return 0;
   }
   if(!owner) owner = TP;
   say(QCTNAME(TP)+" starts to write a message.\n");
   
   if (time_alarm) 
   {
      remove_alarm(time_alarm); /* removes the alarm that destructs this object */
   }
   
   write("Enter your message.\n"
      + "On any line you can give ** to end, or ~q to abort the message.\n");
   gMessage = "";
   write("-->");
   input_to("write_more");
   return 1;
}

float deliv_time(object ob1, object ob2)
{
   if(environment(ob1) == environment(ob2)) return itof(random(10));
   if(explode(MASTER_OB(environment(ob1)),"/")[2] ==
         explode(MASTER_OB(environment(ob2)),"/")[2])
   return itof(20 + random(20));
   return itof(20 + random(20));
} 

int send_mail()
{
   if (gMessage == "")
      {
      NF("Message aborted.\n");
      return 0;
   }
   write("You give the scroll to the "+query_short()+", and it "+
      "clamps it in its mouth.\n");
   say(QCTNAME(TP)+" gives a message to "+
      TP->query_possessive()+" "+query_short()+".\n");
   
   tell_room(environment(TP),"The "+short()+" uncoils around "+QTNAME(TP)+"'s "+ 
      "arm and slithers away.\n",TP);
   TP->catch_msg("The "+short()+" uncoils around your arm and slithers away.\n");
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
	  /* nothing will stop the snake from leaving now */
      time_alarm=set_alarm(SNAKE_TIME,0.0,"return_home"); 
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
   tell_room(room,"The "+query_short()+" slithers away into the shadows.\n");
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
      "back your scroll.\n");
   else
      tell_object(target, capitalize(LANG_ADDART(query_short()))+" "+ 
      "slithers out of the shadows and coils itself around your "+
      "arm. It gives you a scroll from "+capitalize(gSender)+".\n");
   
   tell_room(environment(target),
      "A "+query_short()+" slithers out of the shadows before you!\n"+
      "It coils itself around "+
      "the arm of "+QTNAME(target)+ " and gives "+HIM(target)+" a "+
      "scroll.\n",target);
   
   seteuid(getuid());
   message = clone_object(MESSAGE);
   message->set_message(gMessage);
   message->set_sender(gSender);
   message->move(target);

}

void 
enter_env(object dest, object old)
{
   ::enter_env(dest, old);
   if((gMessage == "") && (dest->query_prop(ROOM_I_IS)))
      set_alarm(itof(random(600)),0.0,"return_home"); 
}     
