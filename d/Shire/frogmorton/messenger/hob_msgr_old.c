/*
 * Based on ~shire/misty/obj/post_rat.c
 * See that file for the history of this file.
 * -- Finwe 2002
 */
 
inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/action";
 
#include "/d/Shire/sys/defs.h"
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "../defs.h"
 
 
#define TEMP_ROOM   (FROG_DIR + "messenger/temp_room")
#define MESSAGE     (FROG_DIR + "messenger/temp_messages")
 
string  gWho, gSender, gMessage = "";
object  owner;
int     gUsage,pigeon_busy,times;

 

void create_creature()
{
    set_name("hobbit");
    add_name("bounder");
    add_name("hobbit messenger");
    add_name("messenger");
    set_pname("hobbit messengers");
    set_gender(random(1));
    set_adj(({"adventuresome"}));
    set_short("adventuresome hobbit messenger");
    set_pshort("adventuresome hobbit messengers");
    set_long("This is an apprentice Bounder from Frogmorton. "+
        CAP(HE_SHE(TP))+ " is learning how to be a member of the Watch, " +
        "the Shirriffs of the Shire. As one of their jobs, they " +
        "must learn their way around by delivering notes. To send " +
        "a message, simply 'send [player]'.\n");
 
    add_prop(OBJ_I_WEIGHT,  1000);
    add_prop(CONT_I_WEIGHT, 1500);
    add_prop(OBJ_I_VOLUME,  2000);
    add_prop(CONT_I_VOLUME, 2000);
    add_prop(OBJ_I_NO_GET, 0);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(OBJ_I_NO_DROP, 0);
    add_prop(LIVE_I_NON_REMEMBER, 1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, " doesn't want anything from " +
        "you, "+HE_SHE(TP)+" just wants to end this adventure " +
        "and go home.\n");

    set_act_time(30+random(60));
    add_act("emote tugs on your sleeve and says: I want to go home!");
    add_act("say I have seen so much on my travels today!");
    add_act("say Where are we headed to now?");
    add_act("say This is so much fun.");
    add_act("say I really should be headed home soon.");


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
	    NF("You are the first sender of a message. You cannot reply.\n");
	    return 0;
	}
	who = gSender;
    }
    /* If a player knows the name of another player, let him send the pigeon. */


    gSender = LOW(TP->query_real_name());
    gWho = LOW(who);

    if (!this_player()->query_met(gWho))
    {
        notify_fail("You do not remember being introduced to anyone named " +
            capitalize(gWho) + ".\n");
        return 0;
    }
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
        ". "+CAP(HE_SHE(TO))+" happily takes it and runs off to " + "deliver it.\n");
    say(QCTNAME(TP)+" gives a message to a " +query_short()+
        ". "+CAP(HE_SHE(TO))+" happily takes it and runs off to " + "deliver it.\n");
 
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
    tell_room(room,"The "+query_short()+" says: 'Thanks for the adventure, it was fun!', and runs off.\n");
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
          "unable to find "+CAP(gWho)+". \n");
    else
        tell_object(target, CAP(LANG_ADDART(query_short()))+
        " runs up to you with a message from " + CAP(gSender)+".\n");
 
    tell_room(environment(target),
      "A "+query_short()+" runs up to " + 
      QTNAME(target)+".\n",target);
 
    seteuid(getuid());
    message = clone_object(MESSAGE);
    message->set_message(gMessage);
    message->set_sender(gSender);
    message->move(target);
//    if (target == owner)
//        call_out("return_home",random(10));
//    else gMessage = "";
}
 
void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);
    if((gMessage == "") && (dest->query_prop(ROOM_I_IS)))
        call_out("return_home",random(10));
}
