inherit "/std/room";
inherit "/d/Genesis/lib/shop";

#include "trade.h"

void
create_room()
{
    set_short("Armorer's");
        set_long(BSS("You have entered Riven's second hand armours "+
                "shop. This is shop sells and buys second hand armours "+
                "of best quality. There is a store room to the west, and an "+
                "exit out to the Shield street east. You can see a "+
                "sign on the wall.\n"));

    add_item("sign", "There is writing on it.\n");


    add_prop(ROOM_I_INSIDE, 1);

        add_exit(SHI_STR+"road1","east",0);
    add_exit("@@query_store_room@@", "west", "@@wiz_check@@", 0);

    config_default_trade();
    set_store_room(SHOP_D + "armory");
}

void
init()
{
    ::init();
add_action("do_read", "read");
    init_shop();
}
int
do_read(string str)
{
    notify_fail("Read what?\n");
    if (str != "sign")
        return 0;

    write("" +
    "You can try these instructions:\n"
 +  "buy platemail for gold and get copper back\n"
 +  "buy platemail for gold coins\n"
 +  "sell platemail for copper coins\n"
 +  "sell all  - will let you sell all items except for\n"
           +  "\nitems you wear.\n"
 +  "sell all! - will let you sell ALL armours you have, well\n"
           +  "\nat least the droppable, and no coins.\n"
 +  "sell platemail, sell second platemail, sell platemail 2,\n"
 +  "sell two platemails also works. You might want to change\n"
           +  "\nthe verb to 'value' or 'buy' too. Beware, you\n"
           +  "\nwill never buy more than one item at a time.\n"
           +  "\nSo if you really those three expensive swords,\n"
           +  "\nyou have to repeat yourself three times.\n"
 +  "If you want a list of all armours available in the store, the\n"
 +  "correct syntax is: list armours 'list weapons', 'list armours'\n"
 +  "also works.\n");
return 1;
}



int
shop_hook_allow_sell(object ob)
{
    if (function_exists("create_object", ob) == "/std/armour")
        return ::shop_hook_allow_sell(ob);
    notify_fail("This shop specializes in armours.\n");
    return 0;
}

int
shop_hook_allow_buy(object ob)
{
    if (function_exists("create_object", ob) == "/std/armour")
        return ::shop_hook_allow_sell(ob);
    notify_fail("This shop specializes in armours.\n");
    return 0;
}

