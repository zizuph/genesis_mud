/* Squirrel farm in Imladris
 * Finwe June 1998
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
 
inherit "/d/Shire/std/room.c";
inherit "/lib/trade";
 
#include <cmdparse.h>
#include <composite.h>
#include <ss_types.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include "/d/Shire/sys/defs.h"
#include "local.h"
 
#define PRICE     30
#define GAVE_SQUIRREL  "_imladris_squirrel"
object squirrelkeeper ;
 
public void
create_shire_room()
{
    config_default_trade();  /* Set up the trading system */
 
    set_short("Elven messenger area");
    set_long("You stand in an airy room. The room is full of " +
        "shelves with many cages holding squirrels. The animals " +
        "appear tame and chitter noisly. The elves use them as " +
        "messengers to keep in contact with others who are away " +
        "for extended periods of time. A sign is attached to the " +
        "wall.\n");
 
 
    add_item("sign","Fine elvish script is enscribed onto it.\n");
    add_cmd_item("sign",
        "read","@@read_sign");
    add_item(({"cage", "cages"}),
        "They are crafted of steel and look secure.\n");
    add_item("squirrels",
        "You see many black dirty rats inside the cage.\n");
    set_alarm(1.0, 0.0, reset_shire_room);
 
    add_exit(VALLEY_DIR + "v_path08", "south");
}
 
string read_sign()
{
    if(!CAN_SEE_IN_ROOM(TP)) return "It is too dark to see.\n";
    return "\n" +
    " If you need to send a message quickly,\n " +
    " you may hire one of our well-trained  \n " +
    " squirrels for a small fee \n\n";
}
 
void init()
{
    ::init();
    add_action("hire_squirrel", "hire");
}

void
reset_shire_room()
{
    if(squirrelkeeper)
    {
        if(present(squirrelkeeper,TO)) return;
        squirrelkeeper->command("shout Ohh... nearly forgot my squirrels!");
        squirrelkeeper->move_living("runs away.",TO);
        tell_room(TO, QCTNAME(squirrelkeeper)+" rushes in.\n");
        squirrelkeeper->command("say Are my squirrels O.K.?");
        return;
    }
    squirrelkeeper = clone_object(RNPC_DIR + "falasia.c");
    squirrelkeeper->arm_me();
    squirrelkeeper->move(TO,1);
    tell_room(TO, QCTNAME(squirrelkeeper)+" walks in.\n");
    squirrelkeeper->command("emote opens some empty cages and " +
        "puts somes squirrels in them.");
}
 
int check_squirrelkeeper()
{
    object enemy;
    string who;
 
    if (squirrelkeeper && present(squirrelkeeper,TO))
    {
        who = TP->query_nonmet_name();
        if(squirrelkeeper->query_introduced(TP))
            who = TP->query_name();
        if(enemy = squirrelkeeper->query_attack())
        {
            if(enemy == TP)
            {
                squirrelkeeper->command("say You want to hire " +
                "a squirrel? Wait till I kill you!");
                squirrelkeeper->command("ponder stupid "+who);
            }
            else
            {
                squirrelkeeper->command("say Please " + who + 
                "! You must wait untill I kill this coward "
                + enemy->query_nonmet_name() + "! " + 
                "Maybe you can help me too?");
                squirrelkeeper->command("wink "+TP->query_name());
            }
            return 0;
        }
        else
            return 1;
    }
    else
    {
        TP->catch_msg("There squirrelkeeper is gone right now. " +
            "You will have to wait until he returns before you " +
            "may hire a squirrel.\n");

        return 0;
    }
}
 
 
int check_light()
{
    if(CAN_SEE_IN_ROOM(squirrelkeeper)) return 1;
    squirrelkeeper->command("say I am sorry "+TP->query_name()+ 
        " but it suddenly got dark in here.");
    squirrelkeeper->command("sigh");
    return 0;
}
 
int query_hire_price(object who)
{
    int bargain;
 
    bargain = TP->query_skill(SS_TRADING);
    if(bargain > 30) bargain = 30;
    bargain = 115 - bargain;
 
    if(TP->query_race_name() == "elf")
        return ((PRICE * bargain * 85) / 10000);
    return ((PRICE * bargain * 120) / 10000);
}
 
int hire_squirrel(string arg)
{
    int price, *arr, error, num;
    object squirrel;
 
    NF("Hire what?\n");
    if(arg != "squirrel") return 0;
 
    if(!check_squirrelkeeper()) return 1;
    if(!check_light()) return 1;
 
 
    price = query_hire_price(TP);
    num = sizeof(query_money_types());
 
    if (sizeof(arr = pay(price, TP, "", 0, 0, "")) == 1)
    {
        squirrelkeeper->command("say You must have money first "+
            TP->query_name()+" before you can hire my nice squirrels.");
        return 1;
    }
    if (error = arr[sizeof(arr) - 1])
    {
        if (error < -1)
        {
            squirrelkeeper->command("say You cannot afford to hire a " +
                "squirrel, "+QCNAME(TP)+ ". I am sorry.");
            return 1;
        }
    }
    TP->catch_msg("You give "+text(arr[0 .. num - 1])+" to "+
      QTNAME(squirrelkeeper)+".\n");
    say(QCTNAME(TP)+" gives "+text(arr[0 .. num - 1])+" to "+
      QTNAME(squirrelkeeper)+".\n");
    if (text(arr[num .. 2 * num - 1]))
    {
        TP->catch_msg("You receive "+text(arr[num .. 2 * num - 1])+
            " back in change.\n");
        say(QCTNAME(squirrelkeeper)+" gives some money back to "+
          QTNAME(TP)+".\n");
    }
    TP->catch_msg(QCTNAME(squirrelkeeper)+ " gets a squirrel " +
        "from the cage and gives it to you.\n");
    say(QCTNAME(squirrelkeeper)+" gets a squirrel from a cage " +
        "and gives it to " + QTNAME(TP)+".\n");
 
    squirrel = clone_object(COURIER_DIR + "squirrel");
    if (squirrel->move(TP))
    {
        squirrel->move(TO);
        squirrelkeeper->command("say Seems that you can't hold it.");
        squirrelkeeper->command("comfort "+TP->query_name());
    }
    return 1;
}
