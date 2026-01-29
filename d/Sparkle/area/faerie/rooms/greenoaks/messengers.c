/* Chipmunk Messengers of Green Oaks
 * By Finwe, August 2004
 * Modified from the following:
 * Rat farm in Goblin caves
 * Milan March 1994
 * modified from:
 *  Shop in Minas Morgul
 *  Olorin, July 1993
 *  copied from:
 *  Bendar's General Store in Edoras
 *  rewritten by Olorin                   may 1993
 *  - use /lib/shop  - copied from ranger guild shop
 *  modified by Olorin                   feb 1993
 *  after ideas by Hamurabbi
 *  after the Hobbiton drug store by
 *                               Tricky, dec 1991
 */

#include "defs.h"
#include <cmdparse.h>
#include <composite.h>
#include <filter_funs.h>
#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
 
inherit "/lib/trade";
inherit INDOORS_BASE;
 
#define PRICE       30
#define GAVE_CHIP   "_ga_chipmunk"

static object quesha;

public void
create_indoor_room()
{
    config_default_trade();  /* Set up the trading system */
 
    set_short("Messenger Service of Green Oaks");
    set_long("This room sits above the post office. It is full of cages " +
        "with tame chipmunks. They are trained as messengers for the " +
        "elves to send news to faraway places. The chipmunks appear " +
        "tame and very friendly. A sign is attached to the wall.\n");
 
 
    add_item("sign","Something is engraved onto it.\n");
 
    add_cmd_item("sign",
        "read","@@read_sign");
 
    add_item(({"cage", "cages"}),
        "The cages are more like large boxes where the chipmunks stay. " +
        "They are very clean, and each holds a chipmunk.\n");
    add_item(({"chipmunk", "chumpmunks",}),
        "They are small rodents trained to deliver messages for elves. " +
        "They are mostly tan with brown strips running down their back. " +
        "Some are sleeping quietly, while others run around their cage " +
        "or chirp happily.\n");
 
     add_exit(GO_DIR + "post", "down");
}
 
string read_sign()
{
    if(!CAN_SEE_IN_ROOM(TP)) return "It is too dark to see.\n";
    return "\n" +
    " If you need to send a message quickly,\n " +
    " you may hire one of our well-trained  \n " +
    " chipmunks for a small fee \n\n";
}
 
void init()
{
    add_action("hire_messenger", "hire");
}

/*
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
 */

int check_chipkeeper()
{
    object enemy;
    string who;
 
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
 
    NF("Hire what, a messenger?\n");
    if(arg != "messenger" ) return 0;
 
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
