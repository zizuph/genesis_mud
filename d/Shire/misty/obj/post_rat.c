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
 *  Palmer April 15, 2006: 
 *  Disable send if you don't have person in memory.
 *
 */

inherit "/std/creature";
inherit "/std/combat/unarmed";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "../local.h"

#define TEMP_ROOM   (CAVE_DIR + "rat_room")
#define MESSAGE     (MISTY_OBJ_DIR + "message")

string  gWho, gSender, gMessage = "";
object  owner;

void create_creature()
{
    set_name("rat");
    set_pname("rats");
    /*
       set_race_name("rat");
    */
    set_adj(({"black","dirty"}));
    set_short("black dirty rat");
    set_pshort("black dirty rats");
    set_long("@@long_func");

    add_prop(OBJ_I_WEIGHT,350);
    add_prop(CONT_I_WEIGHT,350);
    add_prop(OBJ_I_VOLUME,350);
    add_prop(CONT_I_VOLUME,350);
    remove_prop(OBJ_I_NO_GET);
    remove_prop(OBJ_I_NO_DROP);
    add_prop(LIVE_I_NON_REMEMBER,1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, " snaps at you and refuses to take it.\n");

    set_attack_unarmed(0, 5, 5, W_SLASH, 100, "claws");
    set_attack_unarmed(1, 5, 5, W_IMPALE, 100, "teeth");

    set_hitloc_unarmed(0, ({ 5, 7, 3}), 30, "head");
    set_hitloc_unarmed(1, ({ 5, 7, 3}), 70, "body");
}

void init_living()
{
    add_action("do_send","send",0);
}

string long_func()
{
    if (owner && owner != TP)
	return "This is "+owner->query_cap_name()+"'s black dirty rat. It has "+
	"been trained by goblins to deliver messages. You can 'send reply' "+
	"or simply drop it to send it back home.\n";
    return "This is a black dirty rat. It has been trained by goblins to "+
    "deliver messages. You can send a messages to any player by typing "+
    "'send <player>'. If you want to send it back home just drop it.\n";
}

int do_send(string who)
{
    object target;

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
	return 60+random(30);
    return 120+random(60);
} 

int send_mail()
{
    if (!this_player()->query_met(gWho))
    {
        write("You do not remember being introduced to anyone named " +
            capitalize(gWho) + ".\n");
        return 0;
    }

    if (gMessage == "")
    {
	NF("Message aborted.\n");
	return 0;
    }
    write("You give the message to the "+query_short()+".\n");
    say(QCTNAME(TP)+" gives a message to "+
      TP->query_possessive()+" "+query_short()+".\n");

    tell_room(environment(TP),"The "+query_short()+" runs quickly away.\n");
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
    tell_room(room,"The "+query_short()+" runs away.\n");
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
	  "unable to find "+CAP(gWho)+". It gives you " +
	  "back your message.\n");
    else
	tell_object(target, CAP(LANG_ADDART(query_short()))+" runs to you "+
	  "and gives you a message from "+CAP(gSender)+".\n");

    tell_room(environment(target),
      "A "+query_short()+" runs to "+QTNAME(target)+" and gives "+
      target->query_objective()+" a message.\n",target);

    seteuid(getuid());
    message = clone_object(MESSAGE);
    message->set_message(gMessage);
    message->set_sender(gSender);
    message->move(target);
    if (target == owner)
	call_out("return_home",random(10));
    else gMessage = "";
}

void 
enter_env(object dest, object old)
{
    ::enter_env(dest, old);
    if((gMessage == "") && (dest->query_prop(ROOM_I_IS)))
	call_out("return_home",random(10));
}     
