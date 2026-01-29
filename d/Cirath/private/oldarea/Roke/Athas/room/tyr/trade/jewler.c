inherit "/std/room";
inherit "/d/Genesis/lib/shop";

#include "trade.h"

void
create_room()
{
    set_short("Jewlery");
	set_long(BSS("xxx" +
		"xxx"));

    add_prop(ROOM_I_INSIDE, 1);

	add_exit(SUL_STR+"road6","south",0);
    add_exit("@@query_store_room@@", "east", "@@wiz_check@@", 0);

    config_default_trade();
    set_store_room(SHOP_D + "jewlery");
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
