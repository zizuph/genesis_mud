// Avenirian brand of 'pigeon'
// if players give the 'child' things, it runs away with them.
// should we restrain the path of the children to Avenir?
// Modification Log:
// 17 January, Cirion:   Made the child take longer if it
//    has to travel to another domain to deliver the message.
// 01 Dec 1997, Lilith: Children can dilver messages to people not 
//    in player memory. Rationale? These are children. Thay can ask
//    questions to find who they are looking for.
// N.B. The child will not deliver objects. If an object is given
//    to the child, it will run away, and the sender will
//    lose both the object and the child.

#pragma strict_types

inherit "/std/monster";

#include "/d/Avenir/common/bazaar/bazaar.h"
#include <flags.h>

#define SLOWLY               random(20) + 40
#define VERY_SLOWLY          random(60) + 120

#define TIMES 10
// Number of times the child will deliver messages
// before it becomes too tired.

/*
 * Global variables:
 */
static string  gMessage, gWho, gSender, gLocation;
static int     gUsage; 

/*
 * Prototypes:
 */
public  int     do_send(string who);
public  int     send_mail(string str);
public  int     do_resend();
public  void    return_home();
private void    deliver();

private string *randomname =  ({"child","waif", "messenger", "urchin", "orphan"});
private string *randomadj = ({"plaintive", "sad", "skinny", "smiling", "tiny", "frail"});

void 
create_monster()
{
   set_name(randomname[random(sizeof(randomname))]);
   set_adj(randomadj[random(sizeof(randomadj))]);
   set_gender(random(2));
   add_name(({"child", "waif", "messenger", "urchin", "orphan"}));
   set_pname(({"waifs", "messengers", "urchins", "children"}));
   set_race_name("human");
   set_short(query_adj() + " " + lower_case(query_name()));
   set_pshort(query_adj()+ " " +query_pname());
   set_long("This "+ short() +" is the orphan of Sybarite "+
        "slaves.\n"+ capitalize(this_object()->query_pronoun()) +
        " earns "+ this_object()->query_possessive() +" food and "+
        "a corner to sleep in by running messages for "+ 
        this_object()->query_possessive() +" master or mistress.\n"+
        "Write your letter using: 'send <name>' or 'send reply' "+
        "and then the child will deliver it for you.\n");

   gUsage = 0;
   NEVERKNOWN;
   remove_prop(OBJ_I_NO_GET);
   remove_prop(OBJ_I_NO_DROP);
   add_prop(LIVE_I_NON_REMEMBER,1);
   remove_prop(NPC_M_NO_ACCEPT_GIVE);
   add_prop(OBJ_I_WEIGHT,  1000);
   add_prop(CONT_I_WEIGHT, 1500);
   add_prop(OBJ_I_VOLUME,  2000);
   add_prop(CONT_I_VOLUME, 2000);

}

public void 
return_home() 
{
    object room;
    if (living(room = environment()))
        room = environment(room);
    tell_room(room,
        "The "+ short() +" seizes the opportunity and makes "+
        "a run for home.\n");
    remove_object();
}

public int 
do_send(string who)
{
    string  known, intro, remem;
    object  target, tp = TP;

    if (!strlen(who))
	return 0;

    if (tp != ENV(TO))
	return 0;

    if (gUsage >= TIMES)
    {
        notify_fail("The "+ short() +" is too tired to deliver "+
            "another message.\n");
        return 0;
    }

    if (who == "reply" || who == "again")
    {
	/* Has a message been written before? */
        if (!gUsage)
	{
            notify_fail("You are the first sender of a message. You cannot reply.");
            return 0;
        }
        who = gSender;
    }

    gWho = who;
    target = find_player(gWho);

    if (!target)
    {
        notify_fail("That person is sleeping!\n");
        return 0;
    }

   /*
    * Checks for busy wizards, as suggested by Mercade on 4 May 1996
    */
    if (target->query_wiz_level())
    { 
        if (target->query_prop(WIZARD_I_BUSY_LEVEL) & BUSY_M)
        {
            NF("That wizard does not want to be disturbed just now.\n");
            return 0;
        }
    }

    if (target->query_prop(OBJ_I_INVIS))
    {
        notify_fail("Send a message to who?\n");
        return 0;
    }

    gSender = lower_case(tp->query_real_name());
    write("Write your letter:\n"+
        "On any line you can give ** to end, or ~q to abort the message.\n"+
        "---------------------------------------------------------------\n");
    clone_object("/obj/edit")->edit("send_mail");
    return 1;
}

public int 
send_mail(string txt)
{
    object env, where;

    if (!strlen(txt))
    {
	notify_fail("Letter aborted.");
	return 0;
    }

    gMessage = txt;

    write("You give the letter to the "+ short() + ".\n");
    say(QCTNAME(this_player()) + " gives a letter to the "+
        short() +" acting as "+ this_player()->query_possessive() + 
        " messenger.\n");

    if (!(this_player()->query_wiz_level()))
        env = environment(this_player());
    tell_room(environment(this_player()),
        "The "+ short() +" folds the paper up, puts it in an "+
        "envelope, and seals it.\n"+ 
        capitalize(this_object()->query_pronoun()) +" then dashes "+
        "off as fast as "+ this_object()->query_pronoun() +" can.\n");

    where = ENV(find_player(gWho));
    if (where->query_domain() == ENV(TP)->query_domain())
    {
        /* Move the object to a temporary room */
        move(INTR + "waitroom", 1);
        set_alarm(itof(SLOWLY), 0.0, deliver);
        return 1;
    }
    else
    {
        /* Move the object to a temporary room */
        move(INTR + "waitroom", 1);
        set_alarm(itof(VERY_SLOWLY), 0.0, deliver);
        return 1;
    }
}

public int 
do_resend()
{
    object target;

    if (!strlen(gSender) || !strlen(gWho) || 
        (TP != find_player(gSender)))
    {
        notify_fail("You cannot resend if you have not sent first!\n");
        return 0;
    }

    if (objectp(target = find_player(gWho)))
    {
        write("You convince the "+ short()+ " to make yet another try.\n");
        move(INTR + "waitroom", 1);
        set_alarm(itof(VERY_SLOWLY), 0.0, deliver);
        return 1;
    }

    notify_fail("The "+ short() +" does not seem willing to try again.");
    return 0;
}

public void 
deliver() 
{
    object target, message;
    string not_found;

    target = find_player(gWho);
    if (!target || target->query_linkdead())
    {
        target = find_player(gSender);
        if (!target || target->query_linkdead())
        {
            remove_object();
            return;
        }
        else
        {
            not_found = "Sorry, but I couldn't find "+ 
            capitalize(gWho) + " anywhere!\n";
        }
    }

    if (!not_found)
        not_found = "I have a letter for you from "+ 
                    capitalize(gSender) + "!\n";
    if (move(target))
        move(ENV(target));

    tell_object(target, "A "+ short() +" arrives.\nThe "+ short() + 
        " grabs onto your leg and won't let go.\n"+ 
        capitalize(this_object()->query_pronoun()) +" hands you a "+
        "letter and says: " + not_found);
    tell_room(environment(target), "A "+ short() + " arrives.\n"+
        capitalize(this_object()->query_pronoun()) +" runs up to "+ 
        QTNAME(target) + " and clings to "+ target->query_possessive()+ 
        " leg. After catching its breath, the child gives "+ 
        target->query_objective() + " a letter.\n", target);

    message = clone_object("/d/Avenir/common/bazaar/Obj/misc/letter");
    message->set_message(gMessage);
    message->set_sender(gSender);
    message->move(target);
    gMessage = "";
    gUsage++;

    if (gUsage >= TIMES)
        set_alarm(10.0, 0.0, return_home);
}

/* 
 * Function name: enter_inv
 * Description:   Called when objects enter this container or when an
 *                object has just changed its weight/volume/light status.
 * Arguments:     ob: The object that just entered this inventory
 *                from: The object from which it came.
 */
void
enter_inv(object obj, object from)
{
    ::enter_inv(obj,from);
    if (!from) 
        return; // Was probably cloned into me. 
    set_alarm(2.0, 0.0, return_home); 
    // This will make the child run away if given anything except a
    // message to deliver.
}

void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);

    if (dest->query_sublocs() == "av_ch_subloc")
        return;
    if (interactive(dest))
      dest->add_subloc("av_ch_subloc",this_object());
}

void
leave_env(object from, object to)
{
    ::leave_env(from, to);

    if (interactive(from))
        from->remove_subloc("av_ch_subloc");
}

/*
 * Function name: show_subloc
 * Description  : Shows the specific sublocation description for a living.
 * Arguments    : string subloc  - the subloc to display.
 *                object me      - the object to which the subloc is linked.
 *                object for_obj - the object that wants to see the subloc.
 * Returns      : string - the subloc description.
 */
public string
show_subloc(string subloc, object me, object for_obj)
{
    string str;

    if (interactive(environment(this_object())))
        me = environment(this_object());
    else
        return "";

    if (subloc != "av_ch_subloc")
        ::show_subloc(subloc, me, for_obj);

    if (me->query_prop("_temp_subloc_show_only_things"))
        return "";

    if (for_obj == me)
        str = "You have a " + short() + " clinging to your ";
    else
        str = capitalize(me->query_pronoun()) + " has a " +
         short() +" clinging to " + me->query_possessive() + " ";
    return str + "leg.\n";
}

public void 
init_living()
{
    ::init_living();
    add_action(do_send,   "send");
    add_action(do_resend, "resend");
}

