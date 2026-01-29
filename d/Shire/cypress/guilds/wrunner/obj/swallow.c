/*
 * Based on ~shire/misty/obj/post_rat.c
 * See that file for the history of this file.
 * -- Finwe 2002
 *
 * Modification log:
 *
 * -- Toby, 01-Oct-2007: Fixed typo.
 */

#include "/d/Shire/cypress/sys/defs.h"
#include "/d/Shire/cypress/guilds/wrunner/wrunner_defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/action";

#define TEMP_ROOM   (ROOM_DIR + "temp_spar")
#define MESSAGE     (GUILD_OBJ_DIR + "message")

/* The delay between sending the message and the receiving of it. */
#define SLOWLY random(20) + 30


string  gWho, gSender, gMessage = "";
object  owner;
int     gUsage,pigeon_busy;
int     times = 0;

void create_creature()
{
    set_name("swallow");
    set_pname("swallows");
    set_race_name("bird");
    set_adj(({"small","alert"}));
    set_short("small alert swallow");
    set_pshort("small alert swallows");
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
    add_prop(LIVE_I_NON_REMEMBER, 1);
    set_attack_unarmed(1, 5, 5, W_IMPALE, 100, "beak");
    set_hitloc_unarmed(1, ({ 5, 7, 3}), 100, "body");



    set_act_time(30+random(60));
    add_act("emote leaps into the air, beating its wings rapidly for " +
        "a few moments, and lands on your shoulder.");
    add_act("emote chirps excitedly.");
    add_act("emote flies down to the ground and pecks at something, and flies back to you.");
    add_act("emote pecks you on the cheek lightly.");
    add_act("emote cocks its head back and forth a few times.");
}

void init_living()
{
    add_action("do_send","send");
    add_action("return_home","return");
    add_action("do_resend","resend");


}

string long_func()
{
    if (owner && owner == TP)
    return "This is a small swallow trained by the Wild Elves to deliver " +
        "messages. It is blue with a rust-colored underbelly. You can " +
        "send messages via 'send <name>'" +
#if times > 0
    " or 'send reply'" +
#endif
    ". If the swallow fails to deliver the message, you may ask it to " +
    "try again with the 'resend' command. You may 'return swallow' when " +
    "you are done with it.\n";

    if (owner && owner != TP)
        return "This is "+owner->query_cap_name()+"'s swallow and was " +
            "trained by the Wild Elves to send messages. This may be done " +
            "with 'send <name>' or 'send reply'. You may also 'return " +
            "swallow' when you are finished with it.\n";

    return "This is a small swallow trained by the Wild Elves to deliver " +
        "messages. It is blue with a rust-colored underbelly. You can " +
        "send messages via 'send <name>'. You may also 'return swallow' " +
        "when you are finished with it.\n";
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
    target = find_player(gWho);

    // cannot use this to send messages to wizards.
    if (target->query_wiz_level()) 
    {
        NF("You cannot send a message to a wizard. You should mail them instead.\n");
        return 0;
    }

    /* It is useless to write a message to someone who isn't in the game. */
    if (!target)
    {
	    NF("There is no one by that name logged in at the moment.\n");
	    return 0;
    }

    if(!owner) owner = TP;

    say(QCTNAME(TP)+" starts to write message.\n");
    write("Enter your message.\n"
      + "On any line you can give ** to end, or ~q to abort the message.\n");
    gMessage = "";
    write("-->");
    input_to("write_more");
    times = 1;
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

    write("You give your message to the "+query_short() + ". It flies off " +
        "into the distance to deliver it for you.\n");
    say(QCTNAME(TP)+" gives a message to a " +query_short() +
        ". It flies off into the distance.\n");

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

int return_home()
{
    object room;
    if (living(room = environment()))
        room = environment(room);
    tell_room(room,"The " + short() + " chirps excitedly and flies away.\n");
    remove_object();
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
        " flies up to you and lands on your shoulder with a message.\n");

    tell_room(environment(target),
      "A "+query_short()+" flies up to " +
      QTNAME(target)+".\n",target);

    seteuid(getuid());
    message = clone_object(MESSAGE);
    message->set_message(gMessage);
    message->set_sender(gSender);
    message->move(target);
}

void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);
    if((gMessage == "") && (dest->query_prop(ROOM_I_IS)))
        call_out("return_home",random(10));
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
        write("You coax the "+query_real_name()+" to try again.\n");
        move(TEMP_ROOM);
        set_alarm(itof(SLOWLY),0.0,&deliver());
        return 1;
    }

    NF("The " + query_real_name() + " doesn't want to make another try.\n");
    return 0;
}
