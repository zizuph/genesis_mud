/*
 *  Carrier pigeon.
 *  This one can bring a message from one player to another. This will
 *  (ofcourse) take a while. Maybe it's a compensation for the loss of
 *  the 'tell' command.                                  Tricky, dec 1991
 *
 *  Slight modifications by Elessar, March 1992.
 *  Nick was here, May 1992. ** Keep on smiling **
 *  added 'return' from /d/Genesis/obj/pigeon.c, Olorin, July 1993
 * added an outside check to the 'return', Arren 950302
 * Back to the Shire, used as messenger for the Heralds of the Valar
 * Dunstable, 1-6-96
 */

#pragma save_binary

inherit "/std/creature";
inherit "/std/combat/unarmed";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

/* The delay between sending the message and the receiving of it. */
#define SLOWLY random(20) + 30

/* The number of times the pigeon will carry a message. */
#define TIMES 3

#define TEMP_ROOM   ("/d/Shire/herald/tempeagle")
#define MESSAGE     (RANGER_DIR + "obj/message")
#define START_ROOM  ("/d/Shire/herald/start")

//    Prototypes
int return_to(object dest);
void return_home();
int fly_to_someone(object dest);
int deliver();

string  gMessage, gWho, gSender;
int     gUsage,pigeon_busy,times;
object  owner;

varargs int set_times_to_fly(int i)
{
    if (!i) 
	i = TIMES;
    if (i > 10)
	i = 10;
    times = i;
    return 1;
}

void create_creature()
{
    set_name("eagle");
    set_pname("eagles");
    set_race_name("eagle");
    set_adj(({"brown","splotched"}));
    set_short("brown splotched eagle");
    set_pshort("brown splotched eagles");
    set_long("@@long_func");
    gUsage = 0;
    add_prop(OBJ_I_WEIGHT,350);
    add_prop(CONT_I_WEIGHT,350);
    add_prop(OBJ_I_VOLUME,350);
    add_prop(CONT_I_VOLUME,350);
    add_prop(OBJ_I_NO_GET,0);
    add_prop(OBJ_I_NO_DROP,0);
    add_prop(NPC_I_NO_LOOKS,1);
    add_prop(NPC_M_NO_ACCEPT_GIVE," is quite unable to carry anything except a small note.\n");
    set_times_to_fly();
    set_attack_unarmed(1, 5, 5, W_IMPALE, 100, "beak");
    set_hitloc_unarmed(1, ({ 5, 7, 3}), 100, "body");
}

void init_living()
{
    add_action("do_send","send",0);
    add_action("do_return","return",0);
    add_action("do_resend","resend",0);
}

string long_func()
{
    if (owner && owner == TP) 
	return "This is a young eagle, in your service for training. "+
	" You can send messages via 'send <name>'" +
#if TIMES > 1
	" or 'send reply'" +
#endif
	". If the eagle fails to deliver the message you can tell it to " +
	"try again with the 'resend' command.  If you don't want the bird's "+
	" service anymore, you can do 'return eagle'\n.";
    if (owner && owner != TP)
	return "This is "+owner->query_cap_name()+"'s eagle. It is " +
	"however a friendly bird, and you might be able to send messages to " +
	"others by 'send <name>' or 'send reply'. You may also 'return eagle'. "+
	"That will make the bird fly back to "+owner->query_cap_name()+"\n.";
    return "This is a brown splotched eagle, which you can use to send messages "+
    "to others with 'send <name>'.\n";
}

int do_send(string who)
{
    string known, intro, remem;
    object target, tp;

    if (!who || who == "")
	return 0;
    tp = TP;
    if (tp != environment())
	return 0;
    if (gUsage >= times)
    {
	NF("The "+query_real_name()+" refuses to deliver another message.\n");
	return 0;
    }
    if (ENV(tp)->query_prop(ROOM_I_INSIDE))
    {
	NF("You can't send out the "+query_real_name()+" when you're not out in open air.\n");
	return 0;
    }
    if (who == "reply")
    {
	/* Has a message been written before? */
	if (!gUsage)
	{
	    NF("You are the first sender of a message. You cannot reply.\n");
	    return 0;
	}
	who = gSender;
    }
    /* If a player knows the name of another player, let him send the pigeon. */
    gWho = who;
    gSender = lower_case(tp->query_real_name());
    target = find_player(gWho);

    pigeon_busy = 1;
    write("Enter your message.\n"
      + "On any line you can give ** to end, or ~q to abort the message.\n");
    gMessage = "";
    write("-->");
    input_to("write_more");
    return 1;
}

int send_mail()
{
    if (gMessage == "")
    {
	NF("Message aborted.\n");
	return 0;
    }
    write("You give the message to the "+query_real_name()+".\n");
    say(QCTNAME(TP) + " gives a message to "
      + TP->query_possessive() + " "+query_real_name()+".\n");

    tell_room(environment(TP),
      "The "+query_short()+" spreads its wings and soars high into the air.\n");
    /* Move the object to a temporary room */
    move(TEMP_ROOM);
    set_alarm(itof(SLOWLY),0.0,&deliver());
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
	pigeon_busy = 0;
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
	write("You instruct the "+query_real_name()+" to try again.\n");
	move(TEMP_ROOM);
	set_alarm(itof(SLOWLY),0.0,&deliver());
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
      "The "+query_short()+" spreads its wings and flies away.\n");
    remove_object();
}

int test_pigeon_killer(object pl)
{
    if (pl->query_prop("_player_is_pigeon_killer")) 
    {
	tell_object(pl,"The "+query_real_name()+" recognizes you as a killer of birds,"+
	  "and hurriedly flies away again!\n");
	tell_room(ENV(pl),"The "+query_real_name()+" is scared by "+QTNAME(pl)+", and flies away again!\n",pl);
	return_home();
    }
    return 1;
}

int fly_to_someone(object dest)
{
    if (!dest) 
	tell_object(owner,"Bug - no dest.\n");
    if (living(ENV(TO)))
	tell_object(ENV(TO),"The "+query_short()+" spreads its wings and flies up in the sky!\n");
    else 
	tell_room(ENV(TO),"The "+query_short()+" spreads its wings and flies up in the sky!\n");
    if(!dest)
    {
	remove_object();
	return 1;
    }
    TO->move(dest,1);
    tell_object(dest,CAP(LANG_ADDART(query_short())) + " comes flying, and lands on your shoulder.\n");
    tell_room(ENV(dest),CAP(LANG_ADDART(query_short())) +
      " comes flying, and lands on the shoulder of "+QTNAME(dest)+".\n",dest);
    test_pigeon_killer(dest);
    return 1;
}

int return_to(object dest)
{
    if (!dest) 
    {
	return_home();
	return 1;
    }
    if (ENV(dest)->query_prop(ROOM_I_INSIDE))
    {
	return_home();
	return 1;
    }
    pigeon_busy = 0;
    set_alarm(4.0,0.0,&fly_to_someone(dest));
    if (living(ENV(TO)))
    {
	tell_object(ENV(TO),"You hear a whistle from somewhere in the distance.\n");
    }
    else 
	tell_room(ENV(TO),"You hear a whistle from somewhere in the distance.\n");
    return 1;
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
	    if (owner) 
	    { 
		return_to(owner);
		return 1;
	    }
	    remove_object();
	    return 1;
	}
    }
    else if (ENV(target)->query_prop(ROOM_I_INSIDE))
    {
	target = find_player(gSender);
	if (!target)
	{
	    if (owner) 
	    { 
		return_to(owner);
		return 1;
	    }
	    remove_object();
	    return 1;
	}
    }

    /* Go to the target */
    move(target,1);
    pigeon_busy = 0;
    if (target == find_player(gSender))
	tell_object(target, "Your "+query_short()+" returns, " +
	  "unable to find " + CAP(gWho) + ". It lands on " +
	  "your shoulder and you retrieve your message.\n");
    else
	tell_object(target,
	  CAP(LANG_ADDART(query_short())) + " descends from the sky, lands "
	  + "on your shoulder and gives you a message from "
	  + CAP(gSender) + ".\n");

    tell_room(ENV(target),
      CAP(LANG_ASHORT(TO))+" lands on "+QTNAME(target)+"'s shoulder and gives "+
        target->query_objective() + " a message.\n",target);

    message = clone_object(MESSAGE);
    message->set_message(gMessage);
    message->set_sender(gSender);
    message->move(target);
    gUsage++;
    if (gUsage >= times)
	set_alarm(10.0,0.0,&return_home());
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
	if (ENV(TP)->query_prop(ROOM_I_INSIDE))
	{ 
	    NFN("You must be outside to return the " + query_real_name() + ".");
	    return 0;
	}
	write("You send the "+query_real_name()+" up in the air again, to fly back home.\n");
	say(QCTNAME(TP)+" sends the "+query_real_name()+" away.\n",TP);
	if (TP!=owner) 
	    fly_to_someone(owner);
	else 
	    return_home();
	return 1;
    }
    return 0;
}

int query_busy() { return pigeon_busy; }

int set_owner(object player)
{
    if (!player)
	return 0;
    owner = player;
    return 1;
}

int start_place()
{
    TO->move(START_ROOM);
    tell_room(ENV(TO),CAP(LANG_ADDART(query_short())) + " comes flying, landing on the tree branch.\n");
    set_alarm(15.0,0.0,&return_to(owner));
    return 1;
}

void do_die(object ob)
{
    ob->add_prop("_player_is_pigeon_killer",1);
    ::do_die(ob);
}
