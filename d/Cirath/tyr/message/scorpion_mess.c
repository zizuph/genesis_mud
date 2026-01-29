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
* New modifications by Korat 0696
   * -Can be used once only and will not return to sender.
* -Will dissapear after a short time unless it is used.
*/

inherit "/std/creature";
inherit "/std/combat/unarmed";

#include "/d/Cirath/common/defs.h"
#include <wa_types.h>

#define TEMP_ROOM "/d/Cirath/tyr/message/temp_room"
#define MESSAGE "/d/Cirath/tyr/message/message"



string  gWho, gSender, gMessage = "";
object  owner;
int time_alarm;
int TIMES_USED = 0;

void create_creature()
{
   set_race_name("scorpion");
   set_adj(({"shiny","black"}));
   set_short("shiny black scorpion");
   set_long("This shiny black scorpion has been trained to "
   +"deliver messages to people.  It opens and closes its claw "
   +"waiting for a message.  To send a message to someone, use "
   +"'send <player's name>, and the scorpion will rush off to "
   +"deliver it.\n");
    add_prop(OBJ_I_WEIGHT,550);
    add_prop(CONT_I_WEIGHT,550);
    add_prop(OBJ_I_VOLUME,550);
    add_prop(CONT_I_VOLUME,550);
    remove_prop(OBJ_I_NO_GET);
    remove_prop(OBJ_I_NO_DROP);
    add_prop(LIVE_I_NON_REMEMBER,1);

   set_attack_unarmed(0, 5, 5, W_IMPALE, 30, "stinger");
   set_attack_unarmed(0, 5, 5, W_SLASH, 30, "left claw");
   set_attack_unarmed(0, 5, 5, W_SLASH, 30, "right claw");

    set_hitloc_unarmed(0, ({ 5, 7, 3}), 30, "head");
    set_hitloc_unarmed(1, ({ 5, 7, 3}), 70, "body");

}

void init_living()
{
    add_action("do_send","send",0);
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

    if (remove_alarm) {
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
    TP->query_possessive()+" shiny black scorpion.\n");

tell_room(environment(this_player()),"The "+short()+" skitters down "
   +QTNAME(TP)+"'s leg and disappears into the shadows.\n",TP);
  TP->catch_msg("The shiny black scorpion skitters down your leg and "
   +"disappears into the shadows.\n");
    /* Move the object to a temporary room */
    move(TEMP_ROOM);
set_alarm(deliv_time(find_player(gWho),find_player(gSender)),0.0,"deliver",find_player(gSender));
   TIMES_USED += 1;
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
	time_alarm=set_alarm(15.0,0.0,"return_home"); /* nothing will stop the snake from leaving now */
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
	tell_object(target, capitalize(LANG_ADDART(query_short()))+" "+ 
    "skitters from out of a shadow, up your leg, and perches "+
     "on your shoulder.  It gives you a message from "
    +capitalize(gSender)+".\n");

    tell_room(environment(target),
   "A "+query_short()+" skitters from out of the shadows, up "
     +QTNAME(target)+"'s leg and perches on "+HIS_HER(target)+
   " arm, giving "+HIM_HER(target)+" a message.\n",target);

    seteuid(getuid());
    message = clone_object(MESSAGE);
    message->set_message(gMessage);
    message->set_sender(gSender);
    message->move(target);

    if (TIMES_USED >= 2)
    {
	/* make the snake leave for good */
	set_alarm(itof(random(4)),0.0,"return_home");
    }
}

void 
enter_env(object dest, object old)
{
    ::enter_env(dest, old);
    if((gMessage == "") && (dest->query_prop(ROOM_I_IS)))
	set_alarm(itof(random(10)),0.0,"return_home"); 
}     
