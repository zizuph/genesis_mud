inherit "/std/room";
inherit "/d/Emerald/lib/shop_list";

#include "/d/Emerald/defs.h"

void
create_room()
{
    config_default_trade();
    set_money_greed_sell(95);
    set_money_greed_buy(95);
    set_money_give_out(({10000, 500, 10, 2}));
    set_money_give_reduce(({0, 4, 20, 15}));
    set_short("General store of Telseron");
    set_long( "   You are in the general store of Telseron. On the " +
      "walls are display cases showing what the shopkeeper has to " +
      "offer you. You see a staircase leading upstairs to a small " +
      "storeroom. On the counter is a small sign.\n\n");

    add_item("sign", "Rich gold letters are inscribed on it.\n");
    add_item("counter", "It is polished darkwood, with some jars " +
      "and a sign on it.\n");
    add_item( ({ "cases", "display cases" }),  
      "Looking closer at the display cases, you see items which " +
      "available for sale. It would be better to check " +
      "out the price list for a full detail of the items.\n");

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(TOWNSHIP_DIR + "rd23", "out");
    add_exit("@@query_store_room@@", "up", "@@wiz_check@@", 0);

    config_default_trade();
    set_store_room(TOWNSHIP_DIR + "store");
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
