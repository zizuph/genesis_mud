/*
 * Shop of Esgaroth
 * Finwe, February 1998
 */
 
#pragma save_binary
#pragma strict_types
 
inherit "/std/room";
inherit "/d/Emerald/lib/shop_list";
 
#include "local.h"
 
//inherit HOUSE_IN_BASE;
public int do_list(string args);

/* Prototype */
void reset_shire_room();
 
static object shopkeeper;  
 
 
void
create_room()
{
    set_short("The shop of Esgaroth");
    set_long("The shop of Esgaroth. The townspeople of Esgaroth " +
        "are very industrious and sell and trade many things. As " +
        "a result, this shop is a very busy place where they " +
        "can sell a variety of items. Because of this, you are " +
        "liable to find a variety of things that are for sale " +
        "not found in other shops.\n");
 
    config_default_trade();
    set_money_give_max(1000); /* Else things go wrong with "sell all" */
                          /* Copper Silver Gold Platinum  */
    set_money_give_out(   ({ 1000,  700, 4000,    1 })); /* Max_pay   */
    set_money_give_reduce(({    0,    7,    4,    4 })); /* Threshold */

    set_money_greed_sell(105); /* players paid this when selling */
    set_money_greed_buy(95);
    set_store_room(TOWN_DIR + "store");

    set_alarm(1.0, 0.0, reset_shire_room);
     
    add_exit(ROAD_DIR + "road14", "out");
    add_exit("@@query_store_room@@", "up", "@@wiz_check@@", 0);
 
}

public void
fix_keeper()
{
    keeper = clone_object(keeper_file);
    keeper->arm_me();
    keeper->move_living("down", TO);
}

public void
reset_room()
{
    ::reset_room();
    if (!objectp(keeper))
        fix_keeper();
}
 
void
reset_shire_room()
{
 
    if (!shopkeeper)
        shopkeeper = clone_object(NPC_DIR + "shopkeeper");
    if (!present(shopkeeper,this_object()))
        shopkeeper->move(this_object());
 
}
 
 
 
void
init()
{
    ::init();
 
    init_shop();
 
}


public int
do_list(string args)
{
    string list_txt;
    int n, s;
    if (!shopkeeper()) 
    {
        return 0;
    }
    else
    {
        if (args != "supplies" && args)
            return ::do_list(args);
        else 
        {
            if (!args || args == "")
            {
                ::do_list(args);
                write(" *** Supplies available by 'list supplies ***'.\n");
                return 1;
            }
        
            write(" Elven supplies in stock: ----------------------\n");
            s = sizeof(standard_equip);
            while (n < s)
            {
                call_other(standard_equip[n], "load_me");
                shop_hook_list_object(find_object(standard_equip[n]),
                        query_buy_price(find_object(standard_equip[n])));
                n++;
            }
                write(" ----------------------------------------------"+
		      "------------\n");
            return 1;
        }
    }
}
