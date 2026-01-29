/* Customized gift box shop, Gwyneth May, 1999*/

#pragma save_binary

#include <stdproperties.h>
#include "../local.h"
#include "/d/Ansalon/common/defs.h"
#include <macros.h>

inherit "/lib/shop";
inherit KENDERMORE_IN;

#define STORE_ROOM KROOM + "gift_shop2.c"

object nippur;

void
reset_kendermore_room()
{
    if (!nippur)
    {
        nippur = clone_object(KNPC + "nippur");
        nippur->move(TO);
    }
}

void
create_kendermore_room()
{
    config_default_trade();
    set_short("A gift wrapping store");
    set_long("Large pieces of decorated paper are hung from the walls. " + 
        "Bows and ribbons are piled on a table on the east wall. Maybe " + 
        "you can get a present wrapped here. A sign is firmly nailed " + 
        "down to the table.\n");
    add_item(({"bows", "ribbons", "table"}), "Many different colours of " + 
        "bows and ribbons are piled high on the table.\n");
    add_item("sign", "   Welcome to Nippur's Gift Box Shop!\n" + 
                     "   I have several different types of\n" +
                     "   gift boxes for you to choose from.\n" + 
                     "   To order, just do 'order <type>',\n" + 
                     "   and I will make a box of that type\n" + 
                     "   for you to buy.\n" +
                     "\n" + 
                     "   Available Types:\n" + 
                     "   Red, Orange, Yellow, Green, Blue,\n" + 
                     "   Purple, Pink, Silver, Gold, White,\n" +
                     "   Black, Flowered, Plaid, Polka Dot,\n" +
                     "   Heart-shaped, and Striped.\n" +
                     "\n" +
                     "   Boxes are 250cc each.\n" +
                     "\n");
    add_item(({"walls", "paper"}), "The colours dazzle your eye.\n");
    add_exit(KROOM + "street36", "southeast", 0);
    add_invis_exit(STORE_ROOM, "east", "@@wiz_check");
    set_store_room(KROOM + "gift_shop2");
    query_store_room()->load_me();
    reset_kendermore_room();
    return;
}
/* Function name : Init
 * Description : Allows someone to order a gift box of the desired colour. 
 * Returns : Null
*/

void
init()
{
    ::init();
    init_shop();
    add_action("load_box", "order");
}

/* Function name : Enter inventory
 * Description : Starts the room tells when a PC enters the room.
 * Returns : Null
*/

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (interactive(ob))
        start_room_tells();
}

/* Function name : Wiz check
 * Description : Blocks mortals from entering the storeroom.
 * Returns : 1 or 0
*/

int
wiz_check()
{
    if (TP->query_wiz_level())
        return 0;
    write("There is no obvious exit east.\n");
    return 1;
}

/* Function name : Read sign
 * Description : Shows the sign with instructions.
 * Returns : 1
*/

int
do_read(string str)
{
    if (str == "sign")
    {
        write("   Welcome to Nippur's Gift Box Shop!\n" + 
              "   I have several different types of\n" + 
              "   gift boxes for you to choose from.\n" + 
              "   To order, just do 'order <type>',\n" + 
              "   and I will make a box of that type\n" + 
              "   for you to buy.\n" + 
              "   \n" + 
              "   Available Types:\n" + 
              "   Red, Orange, Yellow, Green, Blue,\n" + 
              "   Purple, Pink, Silver, Gold, White,\n" +
              "   Black, Flowered, Plaid, Polka Dot,\n" +
              "   Heart-shaped, and Striped.\n" + 
              "   \n" + 
              "   Boxes are 250cc each\n");

        return 1;
    }
    
}              

/* Functin name : Sell
 * Description : Blocks items from being sold here.
 * Returns : 0
*/

int
do_sell(string str)
{
    NF("You may not sell items here.\n");
    return 0;
}

/* Function : Buy
 * Description : Allows buying while the shopkeeper is present.
 * Returns : 0 or the buy string
*/

int
do_buy(string str)
{
    NF("Nippur must have gotten a severe case of wanderlust and " + 
        "cannot sell you anything.\n");
    if (!P(nippur, TO))
        return 0;

    if (KMASTER->query_enemy(this_player()->query_real_name()))
    {
        write("The shopkeeper won't deal with the likes of you!\n");
        return 1;
    }

    return ::do_buy(str);
}

/* Function name : Load box
 * Description : Starts Nipper making a gift box of the desired colour or
 *     pattern. Checks to see if Nippur is present.
 * Returns : Null
*/

string
load_box(string str)
{
    object box;
    object room = environment(TP);

    if ((nippur)&&((str=="red")||(str=="orange")||(str=="yellow")||(str=="green")||(str=="blue")||(str=="purple")||(str=="pink")||(str=="silver")||(str=="gold")||(str=="flowered")||(str=="plaid")||(str=="polka dot")||(str=="heart-shaped")||(str=="white")||(str=="black")||(str=="striped"))) 
    {
        write ("You ask Nippur for a " + str + " gift box.\n");
        say(QCTNAME(TP) + " asks Nippur for a " + str + " gift box.\n");
        nippur->check_id(str);
        return "";
    }

    if (!nippur)
    {
        write("Nippur isn't here to order from. She must have gotten a " + 
            "severe case of wanderlust, not uncommon for kender.\n"); 
        return "";
    }

    else
    {
        write("Order what kind of gift box?\n");
        return "";
    }
}

