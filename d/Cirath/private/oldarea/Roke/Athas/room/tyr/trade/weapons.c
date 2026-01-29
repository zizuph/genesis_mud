inherit "/std/room";
inherit "/d/Genesis/lib/shop";

#include "trade.h"

void
create_room()
{
    set_short("Weaponry");
 set_long(BSS("This is Riutar's second hand weaponry. We deal with "+
		"fine swords and other second hand weapons. There is a store "+
		"room to the west, and an exit to Sword Street east. You can "+
		"see a sign on the wall.\n"));

    add_item("sign", "There is writing on it.\n");

    add_prop(ROOM_I_INSIDE, 1);

	add_exit(SWO_STR+"road1","east",0);
    add_exit("@@query_store_room@@", "west", "@@wiz_check@@", 0);

    config_default_trade();
    set_store_room(SHOP_D + "weaponry");
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

    if (function_exists("create_object", ob) == "/std/weapon")
        return ::shop_hook_allow_sell(ob);
    notify_fail("This shop specializes in weapons.\n");
    return 0;
}

int
shop_hook_allow_buy(object ob)
{
    if (function_exists("create_object", ob) == "/std/weapon")
        return ::shop_hook_allow_sell(ob);
    notify_fail("This shop specializes in weapons.\n");
    return 0;
}
