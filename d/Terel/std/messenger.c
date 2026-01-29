/* -*- C++ -*- */
 
/*
 * Terel standard messenger
 *
 * All the messengers (pigeons, deliver_mey boys, etc.) in the domain 
 * should inherit this one.
 */
 
#include "/d/Terel/include/Terel.h"
#include <flags.h>

inherit STDCREATURE;

#define WAITROOM  STD_DIR + "messenger/void"
#define LETTER    STD_DIR + "messenger/letter"

/* 
 *  Set defaults for delivery time
 *  Close for in-domain, far for outside of domain
 */

#define WALK_FAR   180
#define WALK_CLOSE 90
#define FLY_FAR    160
#define FLY_CLOSE  80

/*
 * Default number of times that the messenger can be used
 */

#define USES       12

/*
 * Messenger types and default
 */

#define MESG_WALKER  1
#define MESG_FLIER   2
#define MESGR_TYPE   MESG_WALKER


/*
 *  Prototypes
 */
public int set_send_uses(int i);
public int set_messenger_type(int i);
public int set_letter_path(string str);
public int    send_me(string who);
public int    resend_me();
public int    send_mesg(string mesg);
public void   return_me();
private void  deliver_me();


/*
 * Global variables:
 */
public string  gWho, gSender, gMesg, gWhere, gLetter;
public int     gUses, gType, gFar, gNear, gUsage; 



/* 
 * Function name: set_send_uses
 * Description  : sets the number of times the messenger can be sent
 * Arguments    : int i - number we want
 */

public int
set_send_uses(int i)
{
    gUses = i;
}


/* 
 * Function name: set_messenger_type
 * Description  : sets the of messenger 
 * Arguments    : int i - number we want
 * Values       : Walker = 1, Flier = 2
 */

public int
set_messenger_type(int i)
{
    gType = i;
    if (gType == MESG_WALKER)
       {
        gFar  = WALK_FAR;
        gNear = WALK_CLOSE; 
       }
    else
       {
        gFar  = FLY_FAR;
        gNear = FLY_CLOSE;
       }
}

/* 
 * Function name: set_letter_path
 * Description  : sets the file location of the letter object 
 * Arguments    : string str - letter object 
 */

public int
set_letter_path(string str)
{
    gLetter = str;
}

void 
create_messenger()
{
    ::create_creature();
}

nomask void
create_creature()
{
   create_messenger();
   remove_prop(OBJ_I_NO_GET);
   remove_prop(OBJ_I_NO_DROP);
   add_prop(LIVE_I_NON_REMEMBER,1);
   add_prop(LIVE_I_NEVERKNOWN,1);
   add_prop("terel_messenger",1);
   remove_prop(NPC_M_NO_ACCEPT_GIVE);
   add_prop(OBJ_M_NO_SELL, "@@mesg_shop_check");
   set_letter_path(LETTER);
   add_prop(OBJ_M_NO_ATTACK,"One should not blame the messenger for "+
       "bearing bad news.\n");
}

 
int
mesg_shop_check()
{
    if (ETP->query_prop("terel_mesg_shop"))
        return 0;
    return 1;
}


public void 
return_me() 
{
    object room;
    if (living(room = environment()))
        room = environment(room);
    if (gType == MESG_WALKER) 
        tell_room(room, "The "+ short() +" runs for home.\n"); 
    else
        tell_room(room, "With a flap of its wings, the "+ short() 
               +" flies home.\n");
    remove_object();
}

public int 
send_me(string who)
{
    object  target, tp = TP;

    if (!strlen(who))
	return 0;

    if (tp != ENV(TO))
	return 0;

    if (gUsage >= gUses)
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
    write("You begin to write a letter:\n"+
        "On any line you can give ** to end, or ~q to abort the message.\n"+
        "---------------------------------------------------------------\n");
    clone_object("/obj/edit")->edit("send_mesg");
    return 1;
}

public int 
send_mesg(string txt)
{
    object env, where;

    if (!strlen(txt))
    {
	notify_fail("Letter aborted.");
	return 0;
    }

    gMesg = txt;

    write("You give the letter to the "+ short() + ".\n");
    say(QCTNAME(this_player()) + " gives a message to the "+
        short()+".\n");

    if (!(this_player()->query_wiz_level()))
        env = environment(this_player());
    if (gType == MESG_WALKER)
        tell_room(environment(TP),
            "The "+ short() +" takes hold of the message, then dashes "+
            "off to deliver it.\n");
    else
        tell_room(environment(TP),
            "The "+ short() +" takes hold of the message, then flies "+
            "off to deliver it.\n");

    where = ENV(find_player(gWho));
    if (where->query_domain() == ENV(TP)->query_domain())
    {
        /* Move the object to a temporary room */
        move(WAITROOM, 1);
        set_alarm(itof(gNear), 0.0, deliver_me);
        return 1;
    }
    else
    {
        /* Move the object to a temporary room */
        move(WAITROOM, 1);
        set_alarm(itof(gFar), 0.0, deliver_me);
        return 1;
    }
}

public int 
resend_me()
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
        say(CAP(QTNAME(TP)) +" convinces the "+ short()+ " to make yet "
               +"another try.\n");
        move(WAITROOM, 1);
        set_alarm(itof(gFar), 0.0, deliver_me);
        return 1;
    }

    notify_fail("The "+ short() +" does not seem willing to try again.");
    return 0;
}

public void 
deliver_me() 
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
            not_found = "back, having failed to find "+
                         capitalize(gWho) + " anywhere!\n";
        }
    }
    if (gType == MESG_FLIER && ENV(target)->query_prop(ROOM_I_INSIDE))
    {
        target = find_player(gSender);
        if (!target || target->query_linkdead())
        {
            remove_object();
            return;
        }
        else
        {
            not_found = "back, having failed to reach "+ 
            capitalize(gWho) + "!.\n";
        }
    }

    if (!not_found)
        not_found = "from "+ 
                    capitalize(gSender) + ".\n";

    if (move(target))
        move(ENV(target));
 
    if (gType == MESG_WALKER)
        {
        tell_object(target, "A "+ short() +" arrives.\nThe "+ short() + 
            " jumps onto you and won't let go.\n"+ 
            capitalize(PRONOUN(TO)) +" gives you a "+
            "letter " + not_found);
        tell_room(ENV(target),"A "+ short() + " arrives.\n"+
            capitalize(this_object()->query_pronoun()) +" jumps onto "+ 
            QTNAME(target) + " and gives "+ OBJECTIVE(target)+ 
            " a letter.\n",target); 
        }
     else
        {
        tell_object(target, "A "+ short() +" lands on your shoulder.\n"+
            capitalize(PRONOUN(TO)) +" gives you a "+
            "letter " + not_found);
        tell_room(ENV(target), "A "+ short() + " lands on "+
            QTNAME(target) + " and gives "+ OBJECTIVE(target)+ 
            " a letter.\n",target); 
        }


    message = clone_object(gLetter);
    message->set_message(gMesg);
    message->set_sender(gSender);
    message->move(target);
    gMesg = "";
    gUsage++;

    if (gUsage >= gUses)
        set_alarm(10.0, 0.0, return_me);
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
    set_alarm(2.0, 0.0, return_me); 
    // This will make the messenger leave if given anything except a
    // message to deliver.
}
/*
void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);

    if (dest->query_sublocs() == "av_ch_subloc")
        return;
    if (interactive(dest))
      dest->add_subloc("av_ch_subloc",this_object());
}
*/
void
leave_env(object from, object to)
{
    ::leave_env(from, to);

    if (interactive(from))
        from->remove_subloc("av_ch_subloc");
}

public void 
init_living()
{
    ::init_living();
    add_action(send_me,   "send");
    add_action(resend_me, "resend");
}

