/*
 *  /d/Gondor/guild/rangers/obj/ferret.c
 *
 *  A ferret to carry messages within the domains of Gondor and Shire
 *
 *  Modified by Alto, 24 July 2001, directly from:
 *
 *  Carrier pigeon.
 *  This one can bring a message from one player to another. This will
 *  (ofcourse) take a while. Maybe it's a compensation for the loss of
 *  the 'tell' command.                                  Tricky, dec 1991
 *
 *  Slight modifications by Elessar, March 1992.
 *  Nick was here, May 1992. ** Keep on smiling **
 *  added 'return' from /d/Genesis/obj/pigeon.c, Olorin, July 1993
 *  added an outside check to the 'return', Arren 950302
 *  Updated according to changes made in /d/Genesis/obj/pigeon.c,
 *    Olorin, Dec 1996
 *  Remove req. to stay in one place for delivery conf, Gnadnar, Oct 1998
 *  Added check -- can't deliver to invisible players, Gorboth, Apr 1999
 *  Ferret will deliver messages only when both players are present in
 *    the same domain, Alto, Aug 2002.
 *  Updated - fixed indentation and neatened, Gwyneth, May 2004
 *  Fixed runtime error--added check for objectp (line 195)--
 *     Tigerlily, July 2004
 *  Added naming ability to ferrets. Only rangers can name them. 
 *  Names are also logged
 *     Finwe, April 2005
 *
 *  29-Mar-2007, Toby:
 *    Upped time before message is received from 30-50sec to 60-90sec
 *    Lowered amount of times (considerably) the ferret will run back and forth.
 *
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
#define SLOWLY random(30) + 60

/* The number of times the ferret will carry a message. */
#define TIMES   4 + random(4)
#define UNKNOWN "unknown"
#define HIS_HER(o) (o)->query_possessive()

#define TEMP_ROOM   (RANGERS_HQ_DIR + "courier_room")
#define MESSAGE     (RANGERS_OBJ + "message")
#define START_ROOM  (RANGERS_HQ_DIR + "courier_room")
#define FERRET_NAME_LOG (RANGERS_LOG_DIR + "ferret_names")

//#define IS_RANGER(x)    ((x)->query_guild_name_occ() == RANGER_S_GUILD_NAME)
// allows only rangers and ME wizards to name ferret.
#define R_ALLOWED   IS_RANGER(TP) || IS_SHIRE_WIZARD(TP) || IS_GONDOR_WIZARD (TP)


#define LIVE_I_FERRET_KILLER "_live_i_ferret_killer"

/* Global variables: */
static string  gMessage, gWho, gSender, gFerretName, gFerretOwner;
static int     gUsage = 0, gFerretBusy, gTimes, gIsNamed = 0;
static object  gOwner;

/* Prototypes: */
private int     deliver();
public  int     do_send(string who);
public  int     do_return(string str);
public  int     do_resend();
private string  long_func();
public  void    return_home();
public  string  alignlook();
public  string  alignlook2();
public string do_name(string str);



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
    set_short("ferret");
    set_pshort("ferrets");

    set_race_name("ferret");

    set_adj(alignlook());
    add_adj(alignlook2());

    set_long(&long_func());


    add_prop(OBJ_I_WEIGHT,  350);
    add_prop(CONT_I_WEIGHT, 350);
    add_prop(OBJ_I_VOLUME,  350);
    add_prop(CONT_I_VOLUME, 350);
    add_prop(OBJ_I_NO_GET,    0);
    add_prop(OBJ_I_NO_DROP,   0);
    add_prop(NPC_I_NO_LOOKS,  1);
    add_prop(LIVE_I_NON_REMEMBER, 1);
    add_prop(NPC_M_NO_ACCEPT_GIVE,
        " refuses to carry anything except a mail message.\n");

    set_times_to_fly();
    set_attack_unarmed(1, 5, 5, W_IMPALE, 100, "sharp teeth");
    set_hitloc_unarmed(1, ({ 5, 7, 3}), 100, "body");

    /* Male or female */
    set_gender(random(2));
}

string
alignlook()
{
    string *alignlooks = ({"mischievous", "naughty", "stealthy", "bouncy",
                           "clever", "resourceful", "bold", "daring", "deft",
                           "quick","alert","cunning","keen", "intelligent",
                           "alert", "nimble"});

    return one_of_list(alignlooks);
}


string
alignlook2()
{
    string *alignlooks2 = ({"brown", "white", "grey", "calico", "striped",
                            "mottled", "ring-tailed", "black-footed", "black",
                            "scruffy-looking", "one-eyed", "one-eared"});

    return one_of_list(alignlooks2);
}


public void
init_living()
{
    add_action(do_send,   "send");
    add_action(do_return, "return");
    add_action(do_resend, "resend");
    add_action(do_name,   "name");
}

public string
long_func()
{
    string txt = "This lively little ferret seems to have taken a " +
            "liking to you. It scampers about, chittering and chattering, " +
            "looking for mischief. You can send messages to others by " +
            "typing 'send <name>'";


    if (objectp(gOwner) && (gOwner == TP))
        txt +=
            " or 'send reply'. If the ferret fails to deliver the " +
            "message you can tell it to try again with the 'resend' " +
            "command. If you want the ferret back, you can 'whistle " +
            "for ferret', and it will return, assuming it is still " +
            "alive. If you do not want the ferret anymore, you can do " +
            "'return ferret'.";

    else if (objectp(gOwner) && (gOwner != TP))
            txt += " or 'send reply'. You may also 'return " +
                "ferret'. That will make the ferret scamper back to " +
                "its owner.";

    if(gIsNamed == 1)
//        txt = txt + " It was named " + gFerretName + " by " + gFerretOwner;
//        txt = txt + " It is named " + gFerretName;  Toby: changed desc here, only name tag can tell a name
        txt = txt + " A name tag tells its name to be: " + gFerretName;
    else if(IS_RANGER(TP))
        txt = txt + ". You may name this ferret. Do 'name ferret' to learn more";

    return (txt + ".\n");
}

public int
do_send(string who)
{
    string  target_domain, sender_domain;
    object  target, tp = TP, env = ENV(tp), target_env;

        NF("Send whom?\n");
    if (!strlen(who))
        return 0;
    if (tp != ENV(TO))
        return 0;

    if (gUsage >= gTimes)
    {
        NF("The ferret refuses to deliver another message.\n");
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

    gWho = who;


    /*
    if (!this_player()->query_met(gWho))
    {
        notify_fail("You do not remember being introduced to anyone named " +
            capitalize(gWho) + ".\n");
        return 0;
    }
    */

    target = find_player(gWho);
    if (!objectp(target))
    {
        NF("The ferret cannot deliver a message to " +
            capitalize(who) + " at this time.\n");
        return 0;
    }

    target_env = ENV(target);
    target_domain = target_env->query_domain();
    sender_domain = env->query_domain();

    if (sender_domain == target_domain)
    {
        gSender = lower_case(tp->query_real_name());
        gFerretBusy = 1;
        write("Enter your message:\n");
        clone_object(EDITOR_OBJECT)->edit("send_mail");
        return 1;
    }
    else
    {
       NF("Your ferret would not know how to get there.\n");
       return 0;
    }
}

public int
send_mail(string txt)
{
    if (!strlen(txt))
    {
        NF("Message aborted.\n");
        return 0;
    }

    gMessage = txt;
    write("You give the message to the ferret.\n");
    say(QCTNAME(TP) + " gives a message to " + TP->query_possessive() +
        " ferret.\n");
    tell_room(ENV(TP), "The ferret scampers away and quickly " +
        "disappears from sight.\n");

    /* Move the object to a temporary room */
    move(TEMP_ROOM);
    set_alarm(itof(SLOWLY), 0.0, deliver);
    return 1;
}

public int
do_resend()
{
    string  target_domain, sender_domain;
    object  target, tp = TP, env = ENV(tp), target_env;

    if (!strlen(gSender) || !strlen(gWho) || (TP != find_player(gSender)))
    {
        NF("You cannot resend if you have not sent first!\n");
        return 0;
    }

    target = find_player(gWho);
    target_env = ENV(target);
    target_domain = target_env->query_domain();
    sender_domain = env->query_domain();

    if (sender_domain == target_domain)
    {
        if (objectp(target = find_player(gWho)))
        {
            write("You convince the ferret to make yet another try.\n");
            move(TEMP_ROOM);
            set_alarm(itof(SLOWLY), 0.0, deliver);
            return 1;
        }

        NFN("The ferret does not want to make another try.");
        return 0;
    }
    else
    {
       NF("Your ferret would not know how to get there.\n");
       return 0;
    }
}

public void
return_home()
{
    object room;
    if (living(room = ENV(TO)))
        room = ENV(room);

    tell_room(room,
        "The ferret scampers away and quickly disappears from sight.\n");
    remove_object();
}

public int
test_ferret_killer(object pl)
{
    if (pl->query_prop(LIVE_I_FERRET_KILLER))
    {
        tell_object(pl, "The ferret recognizes you as a killer of ferrets, " +
            "and hurriedly scampers away again!\n");
        tell_room(ENV(pl),"The ferret is scared by " + QTNAME(pl) +
            ", and scampers away again!\n", pl);
        return_home();
    }
    return 1;
}

public int
fly_to_someone(object dest)
{
    if (!objectp(dest))
        tell_object(gOwner, "Bug - no destination. Please bug report.\n");

    if (living(ENV(TO)))
        tell_object(ENV(TO),
            "The ferret scampers away and quickly disappears from sight.\n");
    else
        tell_room(ENV(TO),
            "The ferret scampers away and quickly disappears from sight.\n");

    if (!objectp(dest))
    {
        remove_object();
        return 1;
    }

    if (TO->move(dest))
    {
        tell_object(dest, "A ferret scampers in and attempts to climb " +
            "up your leg. But seeing that you are already carrying too " +
            "much, it scampers away again.\n");
        tell_room(ENV(dest), "A ferret scampers in, and tries to climb the " +
            "leg of " + QTNAME(dest) + ", but " + dest->query_pronoun() +
            " is already carrying too much, so it scampers away again.\n",
            dest);
        return_home();
        return 1;
    }

    if (dest->query_invis())
    {
        return_home();
        return 1;
    }

    tell_object(dest, "A ferret scampers in, and climbs up your leg. " +
        "It quickly finds its way to your shoulder, wraps its tail around " +
        "your neck and nibbles at your ear.\n");
    tell_room(ENV(dest), "A ferret scampers in, and climbs up the leg of "
        + QTNAME(dest) + ".\n", dest);
    test_ferret_killer(dest);
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

    gFerretBusy = 0;
    set_alarm(4.0, 0.0, &fly_to_someone(dest));
    if (living(ENV(TO)))
    {
        tell_object(ENV(TO),
            "You hear a whistle from somewhere in the distance.\n");
    }
    else
    {
        tell_room(ENV(TO),
            "You hear a whistle from somewhere in the distance.\n");
        return 1;
    }
}

private void
deliver()
{
    object target, message, env;

    /* Does our initial target still exist? */
    target = find_player(gWho);
    if (objectp(target))
    {
        env = ENV(target);
    }

    /* Does our sender still exist? */
    if (!objectp(target))
    {
        target = find_player(gSender);
        if (objectp(target))
            env = ENV(target);
        else
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
    gFerretBusy = 0;

    tell_room(ENV(target), "A ferret climbs up " + QCTPNAME(target) +
        " shoulder and gives " + target->query_objective() + " a message.\n",
        target);

    if (target == find_player(gSender))
    {
        tell_object(target, ("Your ferret returns, unable to find " +
            CAP(gWho) + ". It climbs up your leg and onto your shoulder. " +
            "You retrieve your message.\n"));
        return;
    }
    else
    {
        tell_object(target, ("A ferret scampers in, climbs up your leg " +
            "and gives you a message.\n"));
    }

    if (ENV(TO) != target)
    {
        target->catch_tell("The ferret scampers off again as it notices " +
            "that you are carrying too much weight.\n");
        tell_room(ENV(target), "The ferret scampers off again as " +
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
        write("You send the ferret off again, to scamper back home.\n");
        say(QCTNAME(TP) + " sends the ferret away.\n", TP);
        if (TP != gOwner)
            fly_to_someone(gOwner);
        else
            return_home();
        return 1;
    }

    return 0;
}

public int
query_busy()
{
    return gFerretBusy;
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
    tell_room(ENV(TO), "A ferret suddenly scampers in and skids across " +
        "the floor.\n");
    set_alarm(15.0, 0.0, &return_to(gOwner));
    return 1;
}

public void
do_die(object ob)
{
    ob->add_prop(LIVE_I_FERRET_KILLER, 1);
    ::do_die(ob);
}

public void
hook_smelled(string str)
{
    string text = short();

    write("The " + text + " smells faintly of musk and herbs.\n");
}


public string do_name(string str)
{
    string temp_name;
    object tp = this_player();

    if(!IS_RANGER(TP))
    {
        write("You may not name this ferret.\n");
        return "";
    }

    if (!str)
    {
        write("You did not provide a name for this ferret.\n");
        return "";
    }

    switch(gIsNamed)
    {
        case 0:
        {

            if (sscanf(str, "ferret %s",temp_name ) == 1)
            {   temp_name = lower_case(temp_name);
                gFerretName = CAP(temp_name);
                write("Placing a name tag on the ferret, you name it: " + CAP(gFerretName) + ". If you do not like this name, you may return the ferret, and call for a new one.\n");
                gIsNamed = 1;
                gFerretOwner = CAP(TP->query_real_name());

                // players can refer to this ferret by the new name
                add_name(lower_case(gFerretName));
                
                if (file_size(FERRET_NAME_LOG) > LOG_SIZE)
                {
	                rename(FERRET_NAME_LOG, (FERRET_NAME_LOG + ".old"));
                }
                    write_file(RANGERS_LOG_DIR + "ferret_names", (ctime(time())) + ": " + gFerretOwner + " named a ferret " + gFerretName + "\n");
                break;
            }

            if( str == "ferret");
            {
                write("If you wish to name this ferret, you may do so with 'name ferret <name>'. Afterwards, the ferret will be known by that name for as long as it's alive.\n\n");
                write("Naturally, use common sense when choosing a name. Vulgar, off-color,  suggestive, or offensive names are not permmited, and may result in punishment.\n");
                break;
            }
        }
        case 1:
        {
            write("This ferret already has a name. You cannot rename it.\n");
            break;
        }
    }

    return "";
}
