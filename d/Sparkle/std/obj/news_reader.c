/*
 * Sparkle News Reader Object
 * 
 * This holds the administration functions for the Sparkle News Server.
 * This item will allow people to post news to the server, and also
 * allow them to delete news if they are wizzies or the owner of the
 * news posted to the server.
 *
 * Created by Lunatari, February 2006
 * Adapted from /secure/mail_reader.c and chipmunk.c by Finw, August 2002
 * 
 * Changes:
 */
#pragma no_inherit
#pragma save_binary
#pragma strict_types

inherit "/std/object";
 
#include "/d/Sparkle/sys/defs.h"

#include <composite.h>
#include <filepath.h>
#include <files.h>
#include <log.h>
#include <language.h>
#include <macros.h>
#include <mail.h>
#include <std.h>
#include <stdproperties.h>
#include <time.h>

#define NF(x)  notify_fail(x)
#define LOW(x) lower_case(x)
#define CAP(x) capitalize(x)
#define ENV(x) environment(x)
 
#define SPARKLE_NEWS (S_DOMAIN_LIB_DIR + "srvr_news")

string  gWho, gSender, gMessage = "";
object  owner;
int     gUsage,pigeon_busy,times;

public void
create_object()
{
    set_name("newsreader");
    add_name("newsread");
    add_name("nreader");

    set_pname("newsreaders");
    add_pname("nreaders");

    add_adj("news");

    set_short(query_name());
    set_pshort(query_pname());

    set_long("This is a news reader. The commands you can use are:\n\n"  +
	     "nread [target] [id]     Reads news from the server.\n"     +
             "npost [target]          Posts news to the server.\n"       +
	     "ndelete [target] [id]   Deletes news from the server.\n\n" +
             "Note: [target] is the targeted club, room or guild, this\n"+
             "      should not be kept zero, other than with the read\n" +
             "      command.\n"                                          +
             "      [id] is the news id number 1-infinity, this should\n"+
             "      also not be zero, see [target]\n\n"                  +
             "That should be all, happy news posting.\n");
  
    add_prop(OBJ_M_NO_DROP,     "There is no reason to drop the reader.\n");
    add_prop(OBJ_M_NO_GIVE,     "You may not give away your newsreader.\n");
    add_prop(OBJ_M_NO_TELEPORT, 1);
    add_prop(OBJ_M_NO_STEAL,    1);
    add_prop(OBJ_M_NO_SELL,     1);
    add_prop(OBJ_M_NO_BUY,      1);

    remove_prop(OBJ_I_WEIGHT);
    remove_prop(OBJ_I_VOLUME);
    remove_prop(OBJ_I_VALUE);
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
	    NF("The chipmunk has never delivered a message before, therefore, " +
            "you cannot reply to anyone.\n");
	    return 0;
	}
	who = gSender;
    }
    /* If a player knows the name of another player, let him send the chipmunk. */
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
    if(ENV(ob1) == ENV(ob2)) return random(5);
    if(explode(MASTER_OB(ENV(ob1)),"/")[2] ==
      explode(MASTER_OB(ENV(ob2)),"/")[2])
        return 30+random(30);
    return 30+random(45);
}
 
int send_mail()
{
    if (gMessage == "")
    {
        NF("Message aborted.\n");
        return 0;
    }
    write("You carefully roll up your message and insert it into the tube on the " + query_short()+
        ". It chitters excitedly and scampers off to deliver it.\n");
    say(QCTNAME(TP)+" carefully rolls up a message and inserts into a tube on a " + query_short()+
        ". It chitters excitedly and scampers off to deliver it.\n");
 
    /* Move the object to a temporary room */
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
          "unable to find "+CAP(gWho)+". \n");
    else
        tell_object(target, CAP(LANG_ADDART(query_short()))+
        " runs up to you with a message from " + CAP(gSender)+". You carefully remove the note from a tube around its neck.\n");
 
    tell_room(environment(target),
      "A "+query_short()+" scampers up to " + QTNAME(target)+".\n",target);
 
    seteuid(getuid());
    //message->set_message(gMessage);
    //message->set_sender(gSender);
    //message->move(target);
}
