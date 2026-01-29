/*
 *  Racial Elemental Clerics Messenger Object.
 *  This object can bring a message from one player to another. This will
 *  (of course) take a while. 
 *
 *  Based off the /d/Genesis/obj/pigeon.c object
 *
 */

#pragma save_binary

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

// The delay between sending the message and the receiving of it.
#define SLOWLY random(20) + 10

#define UNKNOWN "unknown"

string gMessage, gWho, gSender, gLocation;
int times = 2; // This can only be used two times
int gUsage = 0;

string adj1 = "watery";
string mess_desc = "globe";
string mess_departs = "floats up slowly until you can no longer see it";
string mess_arrives = "descends from the sky and lands";

void
set_adj1(string str)
{
	TO->remove_adj(adj1);
	adj1 = str;
	TO->add_adj(adj1);
}

string
query_adj1()
{
	return adj1;
}

void
set_mess_desc(string str)
{
	TO->remove_name(mess_desc);
	mess_desc = str;
	TO->set_name(mess_desc);
	TO->set_pname(mess_desc + "s");
}

string
query_mess_desc()
{
	return mess_desc;
}

void
set_mess_departs(string str)
{
	mess_departs = str;
}

string
query_mess_departs()
{
	return mess_departs;
}

void
set_mess_arrives(string str)
{
	mess_arrives = str;
}

string
query_mess_arrives()
{
	return mess_arrives;
}

string
mess_short()
{
	string short_desc = "small " + adj1 + " " + mess_desc;
	return short_desc;
}

string
mess_pshort()
{
	string pshort_desc = "small " + adj1 + " " + mess_desc + "s";
	return pshort_desc;
}
	
string
mess_long()
{
	string long_desc = "This is a small " + adj1 + " " + mess_desc + ". "+
	    "You can speak to the " + mess_desc + " and have it take the "+
	    "message to someone far away. You can ";
	    	
	if (gUsage >= 1)
	{
		long_desc += "reply to " + capitalize(gSender) +
		    " by typing 'send reply'. ";
	}
	else
	{
		long_desc += "write someone by typing 'send <name>'. ";
	}
	
	long_desc += "If the " + mess_desc + " fails to deliver the message you "+
	    "can get it to try again with the 'resend' command.\nIf you no longer "+
	    "wish to have this " + mess_desc + " you can use the command <destroy "+
	    mess_desc +">.\n";
	
	return long_desc;
}

void
create_object()
{
    set_name(mess_desc);
    set_pname(mess_desc + "s");
    add_name("EC_racial_messenger");
    set_adj(({"small",adj1}));
    set_short("@@mess_short");
    set_pshort("@@mess_pshort"); 
    set_long("@@mess_long");
    add_prop(CONT_I_WEIGHT, 5);
    add_prop(CONT_I_VOLUME, 5);
    add_prop(OBJ_M_NO_GET, 0);
    add_prop(OBJ_M_NO_DROP, "You don't dare drop that!\n");
    add_prop(OBJ_M_NO_GIVE, "You don't dare give that away.\n");
    add_prop(OBJ_M_NO_STEAL, 0);
    add_prop(NPC_M_NO_ACCEPT_GIVE, " does not seem to be able to carry " +
             "anything else but small messages.\n");
}

void
init()
{
    add_action("do_send", "send");
    add_action("resend", "resend");
    add_action("do_destroy", "destroy");
}

int
do_destroy(string str)
{
	if (!str || str != mess_desc)
	{
		notify_fail("Destroy what? The small " + adj1 + " " + mess_desc + "?\n");
		return 0;
	}
	
	write("You cover the small " + adj1 + " " + mess_desc + " with your hands "+
	    "in an attempt to crush it but it disappears before you can do so!\n");
	say(QCTNAME(this_player()) + " covers " + TP->query_possessive() +
        " small " + adj1 + " " + mess_desc + " with " + TP->query_possessive()+
        " hands and it disappears!\n");
    TO->remove_object();
    return 1;
}

int
do_send(string who)
{
    string known, intro, remem;
    object target, tp;

    if (!who || who == "")
        return 0;
 
    tp = this_player();
    if (tp != environment())
        return 0;

    if (gUsage >= times)
    {
        write("The small " + adj1 + " " + mess_desc + " refuses to deliver "+
        	"another message.\n");
        return 1;
    }

    // Has it been used before? If so, are they using 'reply'?
    if (gUsage > 0 && who != "reply")
    {
    	write("You can only <send reply> to send a message back to " +
    	capitalize(gSender) + ".\n");
    	return 1;
    }
    
    if (who == "reply")
    {
        // Has a message been written before?
        if (!gUsage)
        {
            write("You are the first sender of a message. You cannot reply.\n");
            return 1;
        }
        who = gSender;
    }

    // If a player knows the name of another player, let him send the pigeon.
    gWho = who;
    gSender = lower_case(tp->query_name());

    if (!this_player()->query_met(gWho))
    {
        notify_fail("You do not remember being introduced to anyone named " +
            capitalize(gWho) + ".\n");
        return 0;
    }

    // It is useless to write a message to someone who isn't in the game.  
    target = find_player(gWho);
    if (!target)
    {
        write("There is no such player logged in!\n");
        return 1;
    }

    // Save the location of the player. Only if s/he stays, there will be
    // confirmation.
    if (objectp(environment(tp)))
    {
        gLocation = file_name(environment(tp));
    }
    else
    {
        gLocation = UNKNOWN;
    }

    write("Enter your message.\n"
        + "On any line you can give ** to end, or ~q to abort the message.\n");
    gMessage = "";
    write("-->");
    input_to("write_more");
    return 1;
}

void
send_mail()
{
    if (gMessage == "")
    {
        write("Message aborted.\n");
        return;
    }
    write("You whisper the message to the small " + adj1 + " " + mess_desc + ".\n");
    say(QCTNAME(this_player()) + " whispers something to " +
        this_player()->query_possessive() + " small " + adj1 + " " + mess_desc + ".\n");

    tell_room(environment(this_player()), 
        "The small " + adj1 + " " + mess_desc + " " + mess_departs +
        ".\n");

    // Move the object to a temporary room
    move("/d/Krynn/common/void");
    set_alarm(itof(SLOWLY), 0.0, "deliver");
    return;
}

void
write_more(string str)
{
    if (str == "**")
    {
        send_mail();
        return;
    }

    if (str == "~q")
    {
        write("Message aborted.\n");
        return;
    }

    gMessage += (str + "\n");
    write("-->");
    input_to("write_more");
    return;
}

int
resend(string str)
{
    object target;

    if (!gSender || !gWho || this_player() != find_player(gSender))
    {
        notify_fail("You can't resend if you haven't sent first!\n");
        return 0;
    }
 
    if (target = find_player(gWho))
    {
        write("You tell the small " + adj1 + " " + mess_desc + " to make yet another try.\n");
        move("/d/Krynn/common/void");
        set_alarm(itof(SLOWLY), 0.0, "deliver");
        return 1;
    }

    notify_fail("The small " + adj1 + " " + mess_desc + " can't seem to make another try.\n");
    return 0;
}

void
deliver()
{
    object target, message;

    target = find_player(gWho);

    // If the target is not found, the sender is tracked. If s/he moved, the
    // globe is not able to re-locate him/her.
    if (!target)
    {
        target = find_player(gSender);
        if ((gLocation == UNKNOWN) ||
            (objectp(target) && (file_name(environment(target)) != gLocation)))
        {
            target = 0;
        }

        if (!objectp(target))
        {
            remove_object();
            return;
        }
    }

    // Go to the target
    move(target,1);
    if (target == find_player(gSender))
    {
        tell_object(target, break_string("Your small " + adj1 + " " + mess_desc +
            " returns, unable to find " + capitalize(gWho) + ".\n", 70));
        return;
    }
    else
        tell_object(target, break_string(
                "A small " + adj1 + " " + mess_desc + " " +
                mess_arrives + " in your hand and it drops a message from "+ 
                capitalize(gSender) +
                " into it.\n",70));

    tell_room(environment(target),
        "A small " + adj1 + " " + mess_desc + " " + mess_arrives + 
        " in " + QCTNAME(target) +
        "'s hand and drops a message into it.\n",target);

    setuid(); 
    seteuid(getuid());
    message = clone_object("/d/Genesis/obj/message");
    message->set_message(gMessage);
    message->set_sender(gSender);
    message->move(target,1);
    gUsage++;
    if (gUsage >= times)
        set_alarm(5.0, 0.0, "return_home");
}

void
return_home()
{
    object room;
    if (living(room = environment()))
        room = environment(room); 
    tell_room(room,
        "The small " + adj1 + " " + mess_desc + " returns to the "+
        "Elemental Plane that it came from, leaving "+
        "no trace it was ever there.\n");
    remove_object();
}