inherit "/std/room";
inherit "/d/Genesis/lib/shop";
 
#include "/d/Emerald/defs.h"
 
void
create_room()
{
    set_short("Armorer's");
    set_long( "You are in an armorers workshop. On the walls "+
             "you can see some diplomas and a sign, and to the west there "+
             "is a storeroom of sorts.\n" );
 
    add_item("sign", "There is writing on it.\n");
    add_item( ({ "diploma", "diplomas" }), "They all state that the owner "+
             "of the shop is a master craftsman.\n");
 
    add_prop(ROOM_I_INSIDE, 1);
 
    add_exit(TOWNSHIP_DIR + "street_e3_2", "north", 0);
    add_exit("@@query_store_room@@", "west", "@@wiz_check@@", 0);
 
    config_default_trade();
    set_store_room(TOWNSHIP_DIR + "armory");
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
    if (function_exists("create_object", ob) == "/std/armour")
        return ::shop_hook_allow_sell(ob);
    notify_fail("This shop specializes in weapons and armours.\n");
    return 0;
}
 
int
shop_hook_allow_buy(object ob)
{
    if (function_exists("create_object", ob) == "/std/weapon")
        return ::shop_hook_allow_sell(ob);
    if (function_exists("create_object", ob) == "/std/armour")
        return ::shop_hook_allow_sell(ob);
    notify_fail("This shop specializes in weapons and armours.\n");
    return 0;
}
