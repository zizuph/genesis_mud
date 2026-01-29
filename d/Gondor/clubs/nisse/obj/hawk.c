/*
 *  /d/Gondor/clubs/nisse/obj/hawk.c
 *
 *  Primarily coded as a messenger of Nisse Ohtar. But it's not possible to
 *  to give such a messenger to the members of club because of balance issues,
 *  a hawk can be used for doing nice emotes.
 *
 *  Part of this code has been taken from the ranger's pigeon.
 *  Deagol, February 2003
 */

#pragma save_binary
#pragma strict_types

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/action";

#include <const.h>
#include <files.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"
#include "../nisse_defs.h"

/* The delay between sending the message and the receiving of it. */
#define SLOWLY 0

/* The number of times the pigeon will carry a message. */
#define TIMES   4
#define UNKNOWN "unknown"

/*
 *  Global variables:
 */
static string	gMessage, gWho, gSender;
static int	gUsage = 0, 
		gHawk_busy, gTimes;
static object	gOwner;
string		birthmark_colour = TP->query_nisse_rank();
int		hooded;
int		attached;

/*
 *  Prototypes:
 */
private int     deliver();
public  int     do_send(string who);
public  int     do_return(string str);
public  int     do_resend();
public  void    return_home();
string		long_desc();
void		add_acts();

varargs int 
set_times_to_fly(int i)
{
    if (!i) 
        i = TIMES;
    if (i > 10)
        i = 10;

    gTimes = i;
    return 1;
}

public void 
create_creature()
{
    set_name("hawk");
    add_name(NISSE_HAWK_ID);
    set_race_name("hawk");
    set_adj(birthmark_colour);
    set_short(birthmark_colour + " hawk");
    set_long(&long_desc());

    set_gender(G_NEUTER);

    add_prop(OBJ_I_WEIGHT,  350);
    add_prop(CONT_I_WEIGHT, 350);
    add_prop(OBJ_I_VOLUME,  350);
    add_prop(CONT_I_VOLUME, 350);
    add_prop(OBJ_I_NO_GET,    0);
    add_prop(OBJ_M_NO_DROP, "You cannot drop your " + short() + ". Use " +
             "'nihawk return' to send it home.\n");
    add_prop(NPC_I_NO_LOOKS,  1);
    add_prop(LIVE_I_NON_REMEMBER, 1);
    add_prop(NPC_M_NO_ACCEPT_GIVE,
             " refuses your gift since it is not a flesh of its prey.\n");
    set_times_to_fly();
    set_attack_unarmed(1, 5, 5, W_IMPALE, 100, "beak");
    set_hitloc_unarmed(1, ({ 5, 7, 3}), 100, "body");

    setuid();
    seteuid(getuid());

    add_acts();
}

int
do_hunt()
{
    object hawk = present(NISSE_HAWK_ID, TP);
    
    write("Your left arm makes a forceful motion, throwing the " +
        hawk->short() + " up in the air. It soars quickly into the sky, " +
        "circling and looking for prey.\n");
    say(QCTNAME(TP) + "'s left arm makes a forceful motion, throwing " +
        POSSESSIVE(TP) + " " + hawk->short() + " up in the air. It soars " +
        "quickly into the sky, circling and looking for prey.\n");
    hawk->clear_act();
    hawk->seq_clear("_mon_ran_act");
    hawk->set_invis(1);
    TP->remove_subloc(HAWK_SUBLOC_ID);
    return 1;
}

int
clone_prey()
{
    object player = TP;
    object hawk = present(NISSE_HAWK_ID, player);
    
    setuid();
    seteuid(getuid());
    
    clone_object(HAWK_FEED)->move(player);

    write("You hear a keen noise as your " + hawk->short() + " returns " +
        "to you. It carries a " + present(HAWK_FEED_ID, player)->short() +
        " in its sharp talons.\n");
    say("You hear a keen noise as " + QTNAME(player) + "'s " + hawk->short() +
        " returns to its master, carrying a " +
        present(HAWK_FEED_ID, player)->query_short() + " in its sharp " +
        "talons.\n");
    hawk->set_invis(0);
    TP->add_subloc(HAWK_SUBLOC_ID, NISSE_OBJ_DIR + "hawk");
    hawk->seq_reset();
    hawk->add_acts();

    return 1;
}

void
add_acts()
{
    set_act_time(10);

    add_act("emote looks around for prey.");
    add_act("emote flaps its wings fiercely.");
    add_act("emote shrieks loudly.");
    add_act("emote snaps at a passing insect.");
    add_act("emote peers menacingly at you.");
}

public void 
init_living()
{
    ::init_living();
    
//    add_action(do_send,   "send");
//    add_action(do_return, "return");
//    add_action(do_resend, "resend");
}

void
enter_env(object to, object from)
{
    if ((present(NISSE_GLOVE_ID, to)->query_worn()) == 0)
    {
        write("As a " + short() + " makes out you are not wearing " +
            "a falconers glove, it flies away again.\n");
        say("As a " + short() + " makes out " + QTNAME(TP) + " is not " +
            "wearing a falconers glove, it flies away again.\n");
        remove_object();
        return;
    }

    if (living(to))
    {
        to->add_subloc(HAWK_SUBLOC_ID, this_object());
    }

    ::enter_env(to, from);
}

void
leave_env(object from, object to)
{
    if (living(from))
    {
        from->remove_subloc(HAWK_SUBLOC_ID);
    }

    ::leave_env(from, to);
}

string
show_subloc(string subloc, object carrier, object for_obj)
{
    if (carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS) ||
       (subloc != HAWK_SUBLOC_ID))
    {
        return "";
    }

    return ((for_obj == carrier) ? "A " +
        present(NISSE_HAWK_ID, carrier)->short() + " is sitting on your " +
        "left wrist" : "A " + present(NISSE_HAWK_ID, carrier)->short() +
        " is sitting on " + POSSESSIVE(carrier) + " left wrist") + ".\n";
}

string
long_desc()
{
    string text = "You watch the " + short() + ". It is a wonderful " +
        "specimen of an adult bird of prey. It has broad powerful pointed " +
        "wings. The flight feathers are dark and the underwing coverts " +
        "are light.";

    if (!hooded && !attached)
    {
        return text + "\n";
    }
    
    if (hooded && !attached)
    {
        return text + " The hawk is wearing a tiny black hood.\n";
    }
    
    if (!hooded && attached)
    {
        return text + " The hawk is attached to your glove.\n";
    }
    
    return text + " The hawk is wearing a tiny black hood and is attached " +
        "to your glove.\n";
}

public int 
do_send(string who)
{
    string  known, 
            intro, 
            remem;
    object  target, 
            tp = TP,
            env;

    if (!strlen(who))
    {
        notify_fail("Send what?\n", 0);
	return 0;
    }

    if (who != "deagol" && who != "iliana" && who != "sionell" &&
        who != "deagoljr" && who != "reply")
    {
        notify_fail("This hawk works in ptest mode right now, you can send " +
            "it to Deagol, Iliana or Sionell only.\n");
        return 0;
    }

    if (tp != ENV(TO))
    {
	return 0;
    }

    if (gUsage >= gTimes)
    {
	NFN("The " + short() +
	    " refuses to deliver another message.");
	return 0;
    }

    if (who == "reply")
    {
	/* Has a message been written before? */
	if (!gUsage)
	{
	    NFN("You are the first sender of a message. You cannot reply.");
	    return 0;
	}
	who = gSender;
    }
    /* If a player knows the name of another player, let him send a msg. */
    gWho = LOW(who);
    gSender = lower_case(tp->query_real_name());
    target = find_player(gWho);

    gHawk_busy = 1;
    write("Enter your message:\n");
    clone_object(EDITOR_OBJECT)->edit("send_mail");
    return 1;
}

public int 
send_mail(string txt)
{
    if (!strlen(txt))
    {
	NFN("Message aborted.");
	return 0;
    }
    
    gMessage = txt;
    write("You give the message to the " + short() + ".\n");
    say(QCTNAME(TP) + " gives a message to " +
	TP->query_possessive() + " " + short() + ".\n");

    tell_room(ENV(TP), "The " + short() +
	" flaps its wings repeatedly and soars up to the sky.\n");
    /* Move the object to a temporary room */
    move(HAWK_ROOM);
    set_alarm(itof(SLOWLY), 0.0, deliver);
    return 1;
}

public int 
do_resend()
{
    object target;

    if (!strlen(gSender) || !strlen(gWho) || 
	(TP != find_player(gSender)))
    {
	NFN("You cannot resend if you have not sent first!");
	return 0;
    }

    if (objectp(target = find_player(gWho)))
    {
	write("You convince the " + short() + " to make yet another try.\n");
        move(HAWK_ROOM);
	set_alarm(itof(SLOWLY), 0.0, deliver);
	return 1;
    }

    NFN("The " + short() + " does not want to make another try.");
    return 0;
}

public void 
return_home()
{
    object room;
    if (living(room = ENV(TO)))
	room = ENV(room);
    tell_room(room,
	      "The "+query_short()+" flaps its wings repeatedly and " +
	      "soars to circle high above in the sky.\n");
    remove_object();
}

public int 
fly_to_someone(object dest)
{
    if (!objectp(dest)) 
        tell_object(gOwner, "Bug - no dest.\n");

    if (living(ENV(TO)))
        tell_object(ENV(TO),"The "+query_short() + 
            " flaps its wings repeatedly and soars up into the sky!\n");
    else 
        tell_room(ENV(TO),"The "+query_short() + 
            " flaps its wings repeatedly and soars up into the sky!\n");

    if (!objectp(dest))
    {
        remove_object();
        return 1;
    }

    if (TO->move(dest))
    {
        tell_object(dest, CAP(LANG_ADDART(query_short())) + " comes flying, "
          + "and attempts to land on your wrist. But seeing that "
          + "you are already carrying too much, it abandons the landing.\n");
        tell_room(ENV(dest), CAP(LANG_ADDART(query_short())) +
            " comes flying, and tries to land on the wrist of "
          + QTNAME(dest) + ", but " + dest->query_pronoun() + " is already "
          + "carrying too much, so it gives up.\n", dest);
	return_home();
        return 1;
    }

    if (dest->query_invis())  /* the recipient is invisible */
    {
        return_home();
        return 1;
    }

    tell_object(dest, CAP(LANG_ADDART(query_short())) + 
		" comes flying, and lands on your wrist.\n");
    tell_room(ENV(dest), CAP(LANG_ADDART(query_short())) +
        " comes flying, and lands on the wrist of "+QTNAME(dest)+".\n",dest);
    return 1;
}

public int 
return_to(object dest)
{
    if (!objectp(dest)) 
    {
	return_home();
	return 1;
    }

    gHawk_busy = 0;
    set_alarm(4.0, 0.0, &fly_to_someone(dest));
    if (living(ENV(TO)))
    {
	tell_object(ENV(TO), "You hear a whistle from somewhere in the " +
	    "distance.\n");
    }
    else 
	tell_room(ENV(TO), "You hear a whistle from somewhere in the " +
	    "distance.\n");
    return 1;
}

private void 
deliver()
{
    object target, message;

    /* Does our initial target still exist? */
    target = find_player(gWho);
    if (!objectp(target))
    {
	target = 0;
    }
    
    if (target->query_linkdead())
    {
        target = 0;
    }

    /* Does our sender still exist? */
    if (!objectp(target))
    {
	target = find_player(gSender);
	if (!objectp(target))
	{
	    target = 0;
	}
    }

    /* Does our owner still exist? */
    if (!objectp(target))
    {
	return_to(gOwner);
	return;
    }

    /* Go to the target */
    move(target);
    gHawk_busy = 0;

    tell_room(ENV(target),
        "A " + short() + " lands on " + QCTNAME(target) + 
	"'s wrist and gives " + target->query_objective() + 
	" a message.\n",target);
    if (target == find_player(gSender))
    {
	tell_object(target, BSN("Your "+query_short()+" returns, " +
	     "unable to find " + CAP(gWho) + ". It lands on " +
	     "your wrist and you retrieve your message."));
	return;
    }
    else
	tell_object(target, BSN(
      	     CAP(LANG_ADDART(query_short())) + " descends from the sky, lands "
    	     + "on your wrist and gives you a message."));
/*
    if (ENV(TO) != target)
    {
        target->catch_msg("The " + short() + " takes off again as it " +
            "notices that you are carrying too much weight.\n");
        tell_room(ENV(target), "The " + short() + " soon takes off " +
            "again as " + QTNAME(target) + " is carrying " +
            "too much.\n", target);
        move(ENV(target), 1);
        set_alarm(2.0, 0.0, return_home);
    }
*/
    move(target, 1);
    message = clone_object(HAWK_MSG);
    message->set_message(gMessage);
    message->set_sender(gSender);
    message->move(target, 1);
    gUsage++;
    if (gUsage >= gTimes)
	set_alarm(10.0, 0.0, return_home);
}

public int 
do_return(string str)
{
    if (!strlen(str)) 
    {
	notify_fail("Return what?\n", 0);
	return 0;
    }

    if (id(str))
    {
	write("You send the " + short() +
	      " up in the air again, to fly back home.\n");
	say(QCTNAME(TP)+" sends the " + short() + " away.\n",TP);
	if (TP != gOwner) 
	    fly_to_someone(gOwner);
	else 
	    return_home();
	return 1;
    }
    return 0;
}

int 
do_return1()
{
    write("You send the " + short() + " up in the air again, " +
        "to fly back home.\n");
    say(QCTNAME(TP)+" sends the " + short() + " away.\n",TP);

    if (TP != gOwner)
        fly_to_someone(gOwner);
    else 
        return_home();
    return 1;
}

public int query_busy() { return gHawk_busy; }

public int 
set_owner(object player)
{
    if (!objectp(player))
        return 0;
    gOwner = player;
    return 1;
}

void
hood_hawk()
{
    hooded = 1;
}

void
unhood_hawk()
{
    hooded = 0;
}

void
attach_hawk()
{
    attached = 1;
}

void
release_hawk()
{
    attached = 0;
}

int
query_hooded()
{
    if (hooded == 0)
    {
        return 0;
    }
    
    return 1;
}

int
query_attached()
{
    if (attached == 0)
    {
        return 0;
    }
    
    return 1;
}

public void 
do_die(object ob)
{
    ::do_die(ob);
}
