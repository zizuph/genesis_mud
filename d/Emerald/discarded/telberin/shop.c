/*
 * Shop for Telberin
 * Coded by Finwe
 * January 1997
 */
 
inherit "/std/room";
inherit "/d/Emerald/lib/shop_list";
#include "default.h" 
#include "/d/Emerald/defs.h"
 
void
create_room()
{
    config_default_trade();
    set_money_greed_sell(95);
    set_money_greed_buy(95);
    set_money_give_out(({10000, 500, 10, 2}));
    set_money_give_reduce(({0, 4, 20, 15}));
    set_short("General shop of Telberin");
    set_long( "   Standing in the general shop, you see that this " +
        "place is quite busy. Many wares are sold here, some brought " +
        "from other parts of the world. The shopkeeper stays busy as " +
        "he buys and sells stuff to anyone willing to come here. A " +
        "sign sits on the counter.\n\n");
 
    add_item("sign", "Rich gold letters are inscribed on it.\n");
    add_item("counter", "It is polished to a dark sheen with a " +
        "and a sign on it.\n");
 
    add_prop(ROOM_I_INSIDE, 1);
 
    add_exit(AVENUE_DIR + "ave24", "out");
    add_exit("@@query_store_room@@", "up", "@@wiz_check@@", 0);
 
    config_default_trade();
    set_store_room(THIS_DIR + "store");
}
 
void
init()
{
    ::init();
    init_shop();
}
 
/*
int
shop_hook_allow_sell(object ob)
{
    if (function_exists("create_object", ob) == "/std/weapon") 
    {
        notify_fail("This shop doesn't deal with weaponry.\n");
        return 0;
    }   
 
    if (function_exists("create_object", ob) == "/std/armour") 
    {
        notify_fail("This shop doesn't deal with armours.\n");
        return 0;
    }
    return ::shop_hook_allow_sell(ob);
}
 
int
shop_hook_allow_buy(object ob) 
{
    if (function_exists("create_object", ob) == "/std/weapon") 
    {
        notify_fail("This shop doesn't deal with weaponry.\n");
        return 0;
    }   
 
    if (function_exists("create_object", ob) == "/std/armour") 
    {
        notify_fail("This shop doesn't deal with armours.\n");
        return 0;
    }
    return ::shop_hook_allow_buy(ob);
}
*/
