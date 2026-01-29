inherit "/std/room";
inherit "/d/Genesis/lib/shop";

#include "trade.h"

void
create_room()
{
    set_short("General store");
	set_long(BSS("You have entered the General shop of Tyr. Here you " +
		"can sell general things, but not armours, weapons "+
		"or jewelry. There are other stores for that here in "+
		"Tyr. There is a sign on the wall, just behind "+
		"the counter, stating how to use the shop.\n"));

	add_item("sign","There is some writing on it, maybe you should "+
		"try to read it?\n");

    add_prop(ROOM_I_INSIDE, 1);

	add_exit(SUL_STR+"road5","south",0);
    add_exit("@@query_store_room@@", "west", "@@wiz_check@@", 0);

    config_default_trade();
    set_store_room(SHOP_D + "store");
    clone_object("/d/Genesis/obj/deposit")->move(this_object());
}

void
init()
{
    ::init();
    init_shop();
}

int
shop_hook_allow_sell(object ob)
{
    if (function_exists("create_object", ob) == "/std/weapon") {
	notify_fail("This shop doesn't deal with weaponry.\n");
	return 0;
    }
    if (function_exists("create_object", ob) == "/std/armour") {
	notify_fail("This shop doesn't deal with armours.\n");
	return 0;
    }
    return ::shop_hook_allow_sell(ob);
}

int
shop_hook_allow_buy(object ob)
{
    if (function_exists("create_object", ob) == "/std/weapon") {
	notify_fail("This shop doesn't deal with weaponry.\n");
	return 0;
    }
    if (function_exists("create_object", ob) == "/std/armour") {
	notify_fail("This shop doesn't deal with armours.\n");
	return 0;
    }
    return ::shop_hook_allow_buy(ob);
}
