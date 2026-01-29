
/*  Post office in Green Oaks
 *  Also sells chipmunks as messengers
 *  by Finwe, May 2005
 *  Updated by Gronkas July 27, 2016 to fix a typo
 */


#include "defs.h"
#include <cmdparse.h>
#include <composite.h>
#include <filter_funs.h>
#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

//inherit "/std/room";
inherit "/d/Genesis/lib/post";
inherit "/lib/trade";
inherit INDOORS_BASE;

string messages;
int new_mail;
//int test_tour(object player);

#define PRICE       30
#define GAVE_CHIP   "_ga_chipmunk"

static object quesha;

void
create_indoor_room()
{
    setuid(); 
    seteuid(getuid());
    add_prop(ROOM_S_MAP_FILE, "faerie_map.txt");

    config_default_trade();  /* Set up the trading system */

    set_short("The post office of Green Oaks");
    set_long("This is the post office of Green Oaks. It is used by the " +
        "elves who live here to communicate with their friends. It is " +
        "also used by travellers who come to Green Oaks and need to " +
        "stay in contact with others. Many small boxes line a wall where " +
        "mail can be picked up. Several shelves line another wall. They are " +
        "full of cages which hold chipmunks that can be hired as messengers. " +
        "A sign is posted next to them for you to read.\n");

    add_item(({"cage", "cages"}),
        "The cages are more like large boxes where the chipmunks stay. " +
        "They are very clean, and each holds a chipmunk.\n");
    add_item(({"chipmunk", "chumpmunks",}),
        "They are small rodents trained to deliver messages for elves. " +
        "They are mostly tan with brown strips running down their back. " +
        "Some are sleeping quietly, while others run around their cage " +
        "or chirp happily.\n");
    add_item("sign",
        "It is posted on the wall next to the cages. Perhaps you should read it.\n");
    add_item(({"mailboxes", "mailbox", "box", "boxes", "larger box", 
            "small boxes", "many small boxes"}),
        "They are small and square, and set against a wall. Some have " +
        "letters in them.\n");
    add_item(({"shelf", "shelves"}),
        "The several rows of shelves that line the wall hold cages for " +
        "chipmunks. A sign is attached to one of the shelves.\n");
    add_cmd_item("sign", "read","@@read_sign");

    add_exit(GO_DIR + "road04", "north");

}

void
reset_room()
{
    if(quesha)
    {
        if(present(quesha,TO)) return;
        quesha->command("shout Hmm, I need some more chipmunks.");
        quesha->move_living("runs away.",TO);
        tell_room(TO, QCTNAME(quesha)+" rushes in.\n");
        quesha->command("say Ahh, much better. Now we have " +
            "enough messengers.");
        return;
    }
    quesha = clone_object(NPC_DIR + "chip_keeper.c");
    quesha->arm_me();
    quesha->move(TO,1);
    tell_room(TO, QCTNAME(quesha)+" walks in.\n");
    quesha->command("emote carefully puts some chipmunks into clean cages");
}

void
init()
{
    ::init();
    //test_tour(TP);
    post_init();

    add_action("hire_messenger", "hire");

}

leave_inv(ob, to)
{
    ::leave_inv(ob, to);

    post_leave_inv(ob, to);

}

query_mail(silent) 
{
   string name;
   string new;

   name = lower_case(this_player()->query_name());
   if (!restore_object("/d/Genesis/post_dir/"+name) || messages == "")
      return 0;
   if (silent)
      return 1;
   new = "";
   if (new_mail)
      new = " NEW";
   write("\n"+
      "There is"+new+" mail for you in the nearest post office.\n");
   return 1;
}

/*void
tour_done(object player)
{
    player->catch_msg("This appears to be the place you were asked to visit. It is the Post Office of Green Oaks. Above are messengers you may rent to send notes to others. You can now return and to the Minister.\n");
}

void
test_tour(object player)
{
     object  note;

    if (!objectp(note = present(TOUR_NOTE_PROP, TP)))
        return;

    if ((note->query_tour_no() != PO_TOUR_NUM) || (note->query_tour_done()))
    return;

    note->set_tour_done();

    set_alarm(2.0, 0.0, &tour_done(TP));
}*/


/*
 * Messenger routines
 */

 
int check_chipkeeper()
{
    object enemy;
    string who;
 
    setuid(); 
    seteuid(getuid());

    if (quesha && present(quesha,TO))
    {
        who = TP->query_nonmet_name();
        if(quesha->query_introduced(TP))
            who = TP->query_name();
        if(enemy = quesha->query_attack())
        {
            if(enemy == TP)
            {
                quesha->command("say You want to hire a messenger? Wait till I kill you!");
                quesha->command("ponder stupid "+who);
            }
            else
            {
                quesha->command("say Please " + who + "! You must wait " +
                    "untill I kill this coward "
                + enemy->query_nonmet_name() + "! " + "Maybe you can help me too?");
                quesha->command("wink "+TP->query_name());
            }
            return 0;
        }
        else
            return 1;
    }
    else
    {
        TP->catch_msg("The chipmunk keeper is gone right now. You will " +
            "have to wait until he returns before you may hire a messenger.\n");

        return 0;
    }
}
 
 
int check_light()
{
    if(CAN_SEE_IN_ROOM(quesha)) return 1;
    quesha->command("say I am sorry "+TP->query_name()+ 
        " but it suddenly got dark in here.");
    quesha->command("sigh");
    return 0;
}
 
int query_hire_price(object who)
{
    int bargain;
 
    bargain = TP->query_skill(SS_TRADING);
    if(bargain > 30) bargain = 30;
    bargain = 115 - bargain;

 /* gives elves a break since this is their start location  */
    if(TP->query_race_name() == "elf")
        return ((PRICE * bargain * 85) / 10000);
  
    return ((PRICE * bargain * 120) / 10000);
}
 
 
int hire_messenger(string arg)
{
    int price, *arr, error, num;
    object messenger;
 
    NF("Try <hire chipmunk>.\n");
    if(arg != "chipmunk") return 0;
 
    if(!check_chipkeeper()) return 1;
 
    price = query_hire_price(TP);
    num = sizeof(query_money_types());
 
    if (sizeof(arr = pay(price, TP, "", 0, 0, "")) == 1)
    {
        quesha->command("say You must have money first "+
            TP->query_name()+" before you can hire a messenger.");
        return 1;
    }
    if (error = arr[sizeof(arr) - 1])
    {
        if (error < -1)
        {
            quesha->command("say You cannot afford to hire a " +
                "messenger, "+QCNAME(TP)+ ". I am sorry.");
            return 1;
        }
    }
    TP->catch_msg("You give "+text(arr[0 .. num - 1])+" to "+
      QTNAME(quesha)+".\n");
    say(QCTNAME(TP)+" gives "+text(arr[0 .. num - 1])+" to "+
      QTNAME(quesha)+".\n");
    if (text(arr[num .. 2 * num - 1]))
    {
        TP->catch_msg("You receive "+text(arr[num .. 2 * num - 1])+
            " back in change.\n");
        say(QCTNAME(quesha)+" gives some money back to "+
          QTNAME(TP)+".\n");
    }
    TP->catch_msg(QCTNAME(quesha)+ " hands a trained chipmunk to you.\n");
    say(QCTNAME(quesha)+" hands a trained chipmunk to " + 
        QTNAME(TP)+".\n");

    messenger = clone_object(MESS_DIR + "chipmunk");

    if (messenger->move(TP))
    {
        messenger->move(TO);
        quesha->command("say Seems that you can't hold the messenger.");
        quesha->command("comfort "+TP->query_name());
    }

    return 1;
}

string read_sign()
{
    if(!CAN_SEE_IN_ROOM(TP)) return "It is too dark to see.\n";
    return "\n" +
    " If you need to send a message quickly,\n " +
    " you may hire one of our well-trained\n " +
    " chipmunks for a small fee of 30 cc.\n\n";
}
