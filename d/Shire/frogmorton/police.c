/* Police station of Frogmorton who also hires out apprentice 
 * Bounders for messengers. Based on different messenger shops in
 * Middle-earth.
 * -- Finwe, February 2002
 *
 * 2005/11/16 Last update
 * 2011/08/01 Lavellan - Improved plaque etc, fixed light checks and typos.
 */
 
inherit "/d/Shire/std/room.c";
inherit "/lib/trade";
inherit "/d/Genesis/delivery/office";

#include <cmdparse.h>
#include <composite.h>
#include <ss_types.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include "/d/Shire/sys/defs.h"
#include "defs.h"
#include "/d/Genesis/delivery/delivery.h"

 
#define PRICE     30
#define GAVE_MESS  "_frog_messenger"
static object falco;
 
public void
create_shire_room()
{
    config_default_trade();  /* Set up the trading system */
    set_office("Police Headquarters of Frogmorton", 3);

    set_short("Headquarters of the East Farthing Troop of " +
        "the Watch");
    set_long("This is the headquarters of the East Farthing " +
        "Troop of the Watch. The Watch is made up of Bounders " +
        "that keep undesirable outsiders from entering the " +
        "Shire and taking care of Inside Work. Bounders come " +
        "and get their orders from the Shirriffe here for the " +
        "East Farthing. The stone building has little in it " +
        "except for a desk, a chair, a poster, a sign, and a plaque " +
        "on the wall.\n");

    add_item(({"up", "ceiling"}),
        "The ceiling is peaked and made of wood slats\n");
    add_item(({"down", "ground", "floor"}),
        "The floor is made of wood planks. They are swept clean " +
        "and have a worn trail around the desk and from the " +
        "desk to the door.\n");
    add_item(({"wall", "walls"}), 
        "The walls are made of vertical wood planks. Some " +
        "posters are nailed to the walls.\n");
   add_item(({"planks", "slats"}),
        "They are yellow from age and look like they were " +
        "cut from beech.\n");
//        "from beech.\n");
    add_item("desk", 
        "The desk is made of dark maple. It looks well used " +
        "and has some papers scattered across the top.\n");
    add_item("papers",
        "They are orders and instructions for the Troops of " +
        "the East Farthing Watch.\n");
    add_item("poster", 
//        "It is large and covers part of one wall. There is some " +
//        "stuff written on it.\n");
        "It is large and covers part of one wall. There is something " +
        "written on it.\n");
 
    add_cmd_item("poster", "read", "@@read_poster@@");
    add_cmd_item(({"orders", "papers"}), "read", "@@read_orders@@");   

    add_item("sign","Something is engraved onto it.\n");
    add_cmd_item("sign",
        "read","@@read_sign");

    add_item("plaque", "It has writing on.\n");
    add_cmd_item("plaque", "read", "@@read_plaque");
//    add_cmd_item("plaque","read","The sign reads:\nHere you may:\n\n"+
//        "\t<ask for a delivery tour> To get a delivery task.\n"+
//        "\t<deliver>  To deliver an assigned task.\n"+
//        "\t<return>  To return a failed delivery.\n");

    add_exit(FROG_DIR + "road02", "out", 0,1,1);
    add_exit(FROG_DIR + "road02", "east");
    reset_shire_room();
  
}
 
string read_sign()
{
    if(!CAN_SEE_IN_ROOM(TP)) return "It is too dark to see.\n";
    
    say(QCTNAME(TP) + " read the sign on the wall.\n");
    return "\n\n" +
          "        +--------------------------------------------------+\n" +
          "        |  *                                            *  |\n" +
          "        | * *                                          * * |\n" +
          "        |   We have many hobbits in training to become     |\n" +
          "        |   Bounders of the Shire. Part of the training a  |\n" +
          "        |   a Bounder undergoes is to travel the Shire and |\n"+
          "        |   learn where everything is. One way they do     |\n" +
          "        |   that is to be hired as messengers.             |\n" +
          "        |                                                  |\n" +
          "        |   If you need a message delivered, we have many  |\n" +
          "        |   hobbits in training that are happy to help you |\n" +
          "        |   out. All you have to do is 'hire messenger'    |\n" +
          "        |   and one will be assigned to you.               |\n" +
          "        | * *                                          * * |\n" +
          "        |  *                                            *  |\n" +
          "        +--------------------------------------------------+\n\n";
//    say(QCTNAME(TP) + " read the poster on the wall.\n");
}
 
void init()
{
    ::init();
    init_office();
    add_action("hire_messenger", "hire");
}

//int read_orders()
string read_orders()
{
    if(!CAN_SEE_IN_ROOM(TP)) return "It is too dark to see.\n";
    say(QCTNAME(TP) + " reads some papers on the desk.\n");
//    write ("They are orders relating to catching missing animals " +
//        "and keeping track of undesirables in the Shire.\n");
    return "They are orders relating to catching missing animals " +
        "and keeping track of undesirables in the Shire.\n";
//    say(QCTNAME(TP) + " reads some papers on the desk.\n");
//    return 1;
}

//int read_poster()
string read_poster()
{
    if(!CAN_SEE_IN_ROOM(TP)) return "It is too dark to see.\n";
//    write ("\n\n" +
    say(QCTNAME(TP) + " read the poster on the wall.\n");
    return "\n\n" +
          "        +--------------------------------------------------+\n" +
          "        |  *                                            *  |\n" +
          "        | * *                                          * * |\n" +
          "        |   When travelling through the Shire, be careful  |\n" +
          "        |   who you talk to and where you go. Strange      |\n" +
          "        |   travellers have been seen on the Great East    |\n"+
          "        |   Road and even stranger things have been        |\n" +
          "        |   observed. If you see anything unusual, be sure |\n" +
          "        |   to report it to a Bounder who will take care   |\n" +
          "        |   of the situation.                              |\n" +
          "        |                                                  |\n" +
          "        |   Also, be on the lookout for the following:     |\n" +
          "        |                                                  |\n" +
          "        |   * Amanda is looking for her husband. Seems he  |\n" +
          "        |     always leaves with out his lunch. What are   |\n" +
          "        |     we going to do about him? Anyhow, find her   |\n" +
          "        |     to get more information.                     |\n" +
          "        |   * The Shirriffe near Michel Delving needs      |\n" +
          "        |     some help. Rumour has it there are orcs      |\n" +
          "        |     nearby but he needs someone to find them for |\n" +
          "        |     him.                                         |\n" +
          "        |   * Bibbles is having trouble with his cow. See  |\n" +
//          "        |     what you can do yo help him.                 |\n" +
          "        |     what you can do to help him.                 |\n" +
          "        |   * Isembold has run out of hay for his pony. He |\n" + 
          "        |     may need your help.                          |\n" + 
          "        | * *                                          * * |\n" +
          "        |  *                                            *  |\n" +
//          "        +--------------------------------------------------+\n\n");
          "        +--------------------------------------------------+\n\n";
//    say(QCTNAME(TP) + " read the poster on the wall.\n");
//    return 1;
}

string read_plaque()
{
    if(!CAN_SEE_IN_ROOM(TP)) return "It is too dark to see.\n";
    say(QCTNAME(TP) + " read the plaque on the wall.\n");
    return "The plaque reads:\nHere you may:\n\n"+
        "\t<ask for a delivery tour> To get a delivery task.\n"+
        "\t<deliver>  To deliver an assigned task.\n"+
        "\t<return>  To return a failed delivery.\n";
}

void
reset_shire_room()
{
    reset_office();
    
    if(falco)
    {
        if(present(falco,TO)) return;
        falco->command("shout Welcome to Frogmorton");
        falco->move_living("arrives.",TO);
        tell_room(TO, QCTNAME(falco)+" arrives.\n");
        falco->command("say How can I help you?");
        return;
    }
    falco = clone_object(FNPC_DIR + "falco");
    falco->arm_me();
    falco->move(TO,1);
    tell_room(TO, QCTNAME(falco)+" walks in.\n");
    falco->command("emote looks over some papers...");
}
 
int check_falco()
{
    object enemy;
    string who;
 
    if (falco && present(falco,TO))
    {
        who = TP->query_nonmet_name();
        if(falco->query_introduced(TP))
            who = TP->query_name();
        if(enemy = falco->query_attack())
        {
            if(enemy == TP)
            {
                falco->command("say This is a stupid mistake you've made!");
                falco->command("ponder stupid "+who);
            }
            else
            {
                falco->command("say Please, " + who + ", you will " +
                    "have to wait until I kill this coward " +
                enemy->query_nonmet_name() + "! " + 
                    "Maybe you can help me too?");
                falco->command("wink "+TP->query_name());
            }
            return 0;
        }
        else
            return 1;
    }
    else
    {
        TP->catch_msg("Falco is gone right now, taking care of " +
            "some shirrife business. You will have to wait until " +
            "he returns before he can help you.\n");
        return 0;
    }
}
 
 
int check_light()
{
    if(CAN_SEE_IN_ROOM(falco)) return 1;
    falco->command("say I am sorry "+TP->query_name()+ " but it " +
        "suddenly got dark in here.");
    falco->command("sigh");
    return 0;
}
 
int query_hire_price(object who)
{
    int bargain;
 
    bargain = TP->query_skill(SS_TRADING);
    if(bargain > 30) bargain = 30;
    bargain = 115 - bargain;

 /* gives hobbits a break since they are hiring hobbits
  */
    if(TP->query_race_name() == "hobbit")
        return ((PRICE * bargain * 85) / 10000);
  
    return ((PRICE * bargain * 120) / 10000);
}
 
int hire_messenger(string arg)
{
    int price, *arr, error, num;
    object messenger;
 
    NF("Hire what, a messenger?\n");
    if(arg != "messenger" ) return 0;
 
    if(!check_falco()) return 1;
    if(!check_light()) return 1;
 
    price = query_hire_price(TP);
    num = sizeof(query_money_types());
 
    if (sizeof(arr = pay(price, TP, "", 0, 0, "")) == 1)
    {
        falco->command("say You must have money first "+
            TP->query_name()+" before you can hire a messenger.");
        return 1;
    }
    if (error = arr[sizeof(arr) - 1])
    {
        if (error < -1)
        {
            falco->command("say You cannot afford to hire a " +
                "messenger, "+QCNAME(TP)+ ". I am sorry.");
            return 1;
        }
    }
    TP->catch_msg("You give "+text(arr[0 .. num - 1])+" to "+
      QTNAME(falco)+".\n");
    say(QCTNAME(TP)+" gives "+text(arr[0 .. num - 1])+" to "+
      QTNAME(falco)+".\n");
    if (text(arr[num .. 2 * num - 1]))
    {
        TP->catch_msg("You receive "+text(arr[num .. 2 * num - 1])+
            " back in change.\n");
        say(QCTNAME(falco)+" gives some money back to "+
          QTNAME(TP)+".\n");
    }
    TP->catch_msg(QCTNAME(falco)+ " assigns a hobbit messenger to you.\n");
    say(QCTNAME(falco)+" assigns a hobbit messenger to " + 
        QTNAME(TP)+".\n");

    messenger = clone_object(FROG_DIR + "messenger/hob_msgr");

    if (messenger->move(TP))
    {
        messenger->move(TO);
        falco->command("say Seems that you can't hold the messenger.");
        falco->command("comfort "+TP->query_name());
    }
    return 1;
}
