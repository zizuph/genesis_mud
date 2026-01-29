/*
 * Squirrels used as messengers from Imladris
 * Heavily based on the rat, and pigeon. :)
 * By Finwe, June 1998
 *
 * Post rat by Milan. 9.3.94.
 * Time of delivery depends slightly on distance (domains check)
 * It is of course longer than pigeon times...
 * But rats have advantage that they go indoor, can swim well and
 * generally there is almost NO place that rat cant get in.
 *
 * All this is modification of Gondor pigeon.
 *
 *  Carrier pigeon.
 *  This one can bring a message from one player to another. This will
 *  (ofcourse) take a while. Maybe it's a compensation for the loss of
 *  the 'tell' command.                                  Tricky, dec 1991
 *
 *  Slight modifications by Elessar, March 1992.
 *  Nick was here, May 1992. ** Keep on smiling **
 *  added 'return' from /d/Genesis/obj/pigeon.c, Olorin, July 1993
 */
 
inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/action";
 
#include "/d/Shire/sys/defs.h"
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "../local.h"
 
 
#define TEMP_ROOM   (COURIER_DIR + "temp_room")
#define MESSAGE     (COURIER_DIR + "temp_messages")
 
string  gWho, gSender, gMessage = "";
object  owner;
 
void create_creature()
{
    set_name("squirrel");
    set_pname("squirrels");
    set_gender(G_NEUTER);
    set_adj(({"bushy", "grey"}));
    set_short("bushy grey squirrel");
    set_pshort("bushy grey squirrels");
    set_long("This bushy squirrel has been tamed by the elves " +
            "of Imladris. It is grey colored and has a bushy " +
            "tail. It constantly surveys its surroundings for " +
            "any danger. These tame creatures are used to send " +
            "messages back and forth between elves. They have " +
            "graciously allowed others to use them for this " +
            "same purpose. To do so, simply 'send [player]' " +
            "your message.\n");
 
    add_prop(OBJ_I_WEIGHT,350);
    add_prop(CONT_I_WEIGHT,350);
    add_prop(OBJ_I_VOLUME,350);
    add_prop(CONT_I_VOLUME,350);
    add_prop(OBJ_I_NO_GET, 0);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(OBJ_I_NO_DROP, 0);
    add_prop(LIVE_I_NON_REMEMBER, 1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, " chitters at you in disagreement.\n");
 
    set_act_time(30);
    add_act(write("The squirrel chitters nervously at you."));
    add_act(write("The squirrel cleans itself."));
    add_act(write("The squirrel scampers about."));
    add_act(write("The squirrel darts its head back and forth, looking for danger."));
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
    if (who == "reply")
    {
        if(!owner)
        {
            NF("The squirrel can't send you a message.\n");
            return 0;
        }
        who = gSender;
    }
    /* If a player knows the name of another player, send message */
    gSender = LOW(TP->query_real_name());
    gWho = LOW(who);
    target = find_player(gWho);
 
    /* It is useless to write a message to someone who isn't in the game. */
    if (!target)
    {
        NF("The squirrel returns, unable to deliver your message to "
        + who + ".\n");
        return 0;
    }
    if(!owner) owner = TP;
    say(QCTNAME(TP)+" begins to compose a message\n");
    write("Enter your message.\n"
      + "On any line you can give ** to end, ~q to abort the message.\n");
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
        return 60+random(30);
    return 60+random(60);
}
 
int send_mail()
{
    if (gMessage == "")
    {
        NF("Message aborted.\n");
        return 0;
    }
    write("You give your message to the "+query_short()+
        ". It chitters happily and scampers off with your " +
        "message.\n");
    say(QCTNAME(TP)+" gives a message to a " +query_short()+
    ". It chitters happily and scampers off.\n");
 
//    tell_room(environment(TP),"The "+query_short()+" runs quickly away.\n");
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
    tell_room(room,"The "+query_short()+" chitters and dashes away.\n");
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
        tell_object(target, CAP(LANG_ADDART(query_short()))+
        " scampers up to you with a message from "+
        CAP(gSender)+".\n");
 
    tell_room(environment(target),
      "A "+query_short()+" scampers up and gives something to " + 
      QTNAME(target)+".\n",target);
 
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
