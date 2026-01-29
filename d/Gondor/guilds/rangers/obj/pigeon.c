/*
 *  Carrier pigeon.
 *  This one can bring a message from one player to another. This will
 *  (ofcourse) take a while. Maybe it's a compensation for the loss of
 *  the 'tell' command.                                  Tricky, dec 1991
 *
 *  Slight modifications by Elessar, March 1992.
 *  Nick was here, May 1992. ** Keep on smiling **
 *  added 'return' from /d/Genesis/obj/pigeon.c, Olorin, July 1993
 *  added an outside check to the 'return', Arren 950302
 *  Updated according to changes made in /d/Genesis/obj/pigeon.c, Olorin, Dec 1996
 *  Remove req. to stay in one place for delivery conf, Gnadnar, Oct 1998
 *  Added check -- can't deliver to invisible players, Gorboth, Apr 1999
 * Added objectp check for find_player on target, Tigerlily, July 2004
 */
inherit "/std/creature";
inherit "/std/combat/unarmed";

#include <const.h>
#include <files.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"
#include "../rangers.h"

/* The delay between sending the message and the receiving of it. */
#define SLOWLY random(20) + 30

/* The number of times the pigeon will carry a message. */
#define TIMES   3
#define UNKNOWN "unknown"

#define TEMP_ROOM   (RANGERS_HQ_DIR + "courier_room")
#define MESSAGE        (RANGERS_OBJ + "message")
#define START_ROOM  (RANGERS_HQ_DIR + "courier_room")

#define LIVE_I_PIGEON_KILLER "_live_i_pigeon_killer"

/* Global variables: */
static string  gMessage, gWho, gSender;
static int     gUsage = 0, 
               gPigeon_busy, gTimes;
static object  gOwner;

/* Prototypes: */
private int     deliver();
public  int     do_send(string who);
public  int     do_return(string str);
public  int     do_resend();
private string  long_func();
public  void    return_home();

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
    set_name("pigeon");
    set_pname("pigeons");
    set_race_name("pigeon");
    set_adj(({"white", "carrier"}));
    set_short("white carrier pigeon");
    set_pshort("white carrier pigeons");
    set_long(&long_func());
    set_gender(G_NEUTER);
    add_prop(OBJ_I_WEIGHT,  350);
    add_prop(CONT_I_WEIGHT, 350);
    add_prop(OBJ_I_VOLUME,  350);
    add_prop(CONT_I_VOLUME, 350);
    add_prop(OBJ_I_NO_GET,    0);
    add_prop(OBJ_I_NO_DROP,   0);
    add_prop(NPC_I_NO_LOOKS,  1);
    add_prop(LIVE_I_NON_REMEMBER, 1);
    add_prop(NPC_M_NO_ACCEPT_GIVE,
        " is quite unable to carry anything except a mail message.\n");
    set_times_to_fly();
    set_attack_unarmed(1, 5, 5, W_IMPALE, 100, "beak");
    set_hitloc_unarmed(1, ({ 5, 7, 3}), 100, "body");
}

public void 
init_living()
{
    add_action(do_send,   "send");
    add_action(do_return, "return");
    add_action(do_resend, "resend");
}

public string 
long_func()
{
    if (objectp(gOwner) && (gOwner == TP))
        return "This is your personal carrier pigeon. " +
            "You can send messages to others by typing 'send <name>'" +
            " or 'send reply'. If the pigeon fails to deliver the message " +
            "you can tell it to try again with the 'resend' command. If " +
            "you want the pigeon back, you can 'whistle for pigeon', and " +
            "it will return, if it's still alive. If you do not want " +
            "the pigeon anymore, you can do 'return pigeon'.\n";

    if (objectp(gOwner) && (gOwner != TP))
        return "This is a white carrier pigeon. You can send " +
            "messages to others by 'send <name>' or 'send reply'. " +
            "You may also 'return pigeon'. That will make the pigeon " +
            "fly back to its owner.\n";

    return "This is a white carrier pigeon, which you can use " +
        "to send messages to others by 'send <name>'.\n";
}

public int 
do_send(string who)
{
    string  known, intro, remem;
    object  target, tp = TP, env;

    if (!strlen(who))
        return 0;

    if (tp != ENV(TO))
        return 0;

    if (gUsage >= gTimes)
    {
        NF("The pigeon refuses to deliver another message.\n");
        return 0;
    }

    if ((env = ENV(tp))->query_prop(ROOM_I_INSIDE))
    {
       NF("You cannot send out the pigeon when you're not out in open air.\n");
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
    if (!objectp(target))
    {
        NF("The pigeon cannot deliver a message to " +
            capitalize(who) + " at this time.\n");
        return 0;
    }
    gPigeon_busy = 1;
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
    write("You give the message to the pigeon.\n");
    say(QCTNAME(TP) + " gives a message to " + TP->query_possessive() +
        " pigeon.\n");

    tell_room(ENV(TP), "The pigeon flaps its wings and flies up to the sky.\n");

    /* Move the object to a temporary room */
    move(TEMP_ROOM);
    set_alarm(itof(SLOWLY), 0.0, deliver);
    return 1;
}

public int 
do_resend()
{
    object target;

    if (!strlen(gSender) || !strlen(gWho) || (TP != find_player(gSender)))
    {
        NF("You cannot resend if you have not sent first!\n");
        return 0;
    }

    if (objectp(target = find_player(gWho)))
    {
        write("You convince the pigeon to make yet another try.\n");
        move(TEMP_ROOM);
        set_alarm(itof(SLOWLY), 0.0, deliver);
        return 1;
    }

    NF("The pigeon does not want to make another try.\n");
    return 0;
}

public void 
return_home()
{
    object room;
    if (living(room = ENV(TO)))
        room = ENV(room);

    tell_room(room, "The pigeon flaps its wings and flies away.\n");

    remove_object();
}

public int 
test_pigeon_killer(object pl)
{
    if (pl->query_prop("_player_is_pigeon_killer")) 
    {
        tell_object(pl, "The pigeon recognizes you as a killer " +
            "of birds, and hurriedly flies away again!\n");
        tell_room(ENV(pl),"The pigeon is scared by " + QTNAME(pl) +
            ", and flies away again!\n", pl);
        return_home();
    }
    return 1;
}

public int 
fly_to_someone(object dest)
{
    if (!objectp(dest)) 
        tell_object(gOwner, "Bug - no destnation. Please bug report.\n");

    if (living(ENV(TO)))
        tell_object(ENV(TO),"The pigeon flaps its wings and flies " +
            "up into the sky!\n");
    else 
        tell_room(ENV(TO),"The pigeon flaps its wings and flies up " +
            "into the sky!\n");

    if (!objectp(dest))
    {
        remove_object();
        return 1;
    }

    if (TO->move(dest))
    {
        tell_object(dest, "A pigeon comes flying, and attempts to land " +
            "on your shoulder. But seeing that you are already carrying " +
            "too much, it abandons the landing.\n");
        tell_room(ENV(dest), "A pigeon comes flying, and tries to land " +
            "on the shoulder of " + QTNAME(dest) + ", but " +
            dest->query_pronoun() + " is already carrying too much, so it " +
            "gives up.\n", dest);
        return_home();
        return 1;
    }

    if (dest->query_invis())  /* the recipient is invisible */
    {
        return_home();
        return 1;
    }

    tell_object(dest, "A pigeon comes flying, and lands on your shoulder.\n");
    tell_room(ENV(dest), "A pigeon comes flying, and lands on the shoulder " +
        "of " + QTNAME(dest) + ".\n", dest);
    test_pigeon_killer(dest);
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

    if (ENV(dest)->query_prop(ROOM_I_INSIDE))
    {
        return_home();
        return 1;
    }

    gPigeon_busy = 0;
    set_alarm(4.0, 0.0, &fly_to_someone(dest));

    if (living(ENV(TO)))
    {
        tell_object(ENV(TO), "You hear a whistle from somewhere in " +
            "the distance.\n");
    }
    else 
        tell_room(ENV(TO),"You hear a whistle from somewhere in the " +
            "distance.\n");
    return 1;
}

private void 
deliver()
{
    object target, message;

    /* Does our initial target still exist? */
    target = find_player(gWho);
    if (objectp(target) && ENV(target)->query_prop(ROOM_I_INSIDE))
        target = 0;

    /* Does our sender still exist? */
    if (!objectp(target))
    {
        target = find_player(gSender);
        if (objectp(target) && ENV(target)->query_prop(ROOM_I_INSIDE))
            target = 0;
    }

    /* Does our owner still exist? */
    if (!objectp(target))
    {
        return_to(gOwner);
        return;
    }

    /* Go to the target */
    move(target);
    gPigeon_busy = 0;

    tell_room(ENV(target), "A pigeon lands on " + QCTPNAME(target) + 
        " shoulder and gives " + target->query_objective() + 
        " a message.\n", target);
    if (target == find_player(gSender))
    {
        tell_object(target, "Your pigeon returns, unable to find " +
            CAP(gWho) + ". It lands on your shoulder and you retrieve " +
            "your message.\n");
        return;
    }
    else
        tell_object(target, "A pigeon descends from the sky, lands on " +
            "your shoulder and gives you a message.\n");

    if (ENV(TO) != target)
    {
        target->catch_tell("The pigeon takes off again as it notices " +
            "that you are carrying too much weight.\n");
        tell_room(ENV(target), "The pigeon soon takes off again as " +
            QTNAME(target) + " is carrying too much.\n", target);
        move(ENV(target), 1);
        set_alarm(2.0, 0.0, return_home);
    }

    message = clone_object(MESSAGE);
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
        NF("Return what?\n");
        return 0;
    }

    if (id(str))
    {
        if (ENV(TP)->query_prop(ROOM_I_INSIDE))
        { 
            NF("You must be outside to return the pigeon.\n");
            return 0;
        }

        write("You send the pigeon up in the air again, to fly back home.\n");
        say(QCTNAME(TP)+" sends the pigeon away.\n",TP);

        if (TP != gOwner) 
            fly_to_someone(gOwner);
        else 
            return_home();
        return 1;
    }

    return 0;
}

public int query_busy()
{
    return gPigeon_busy;
}

public int 
set_owner(object player)
{
    if (!objectp(player))
        return 0;

    gOwner = player;
    return 1;
}

public int 
start_place()
{
    TO->move(START_ROOM);
    tell_room(ENV(TO), "A pigeon comes flying, landing on the floor.\n");
    set_alarm(15.0, 0.0, &return_to(gOwner));
    return 1;
}

public void 
do_die(object ob)
{
    ob->add_prop("_player_is_pigeon_killer",1);
    ::do_die(ob);
}
