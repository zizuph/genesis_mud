inherit "/std/room";
inherit "/d/Emerald/lib/shop_list";

#include "default.h"
#include <stdproperties.h>
#include <files.h>

void
create_room()
{
    string sign;

    set_short("Eril's armoury");
    set_long("   You are in the shop of the famous elven smith, Eril.  " +
        "When he is not busy forging custom creations for the royals of " +
        "Telberin, he offers his services to its citizens and adventurers.  " +
        "The shop is crowded with shelves and cases displaying many of " +
        "his fine works, some of which may even be for sale.\n" + 
        "A prominent sign hangs on the wall.\n");

    add_item(({ "shelves", "cases" }),
        "Shelves and cases display a number of the smith's creations.\n");

    add_item(({ "creations", "works", "armours", "weapons" }),
        "A wide variety of weapons and armours are displayed in cases " +
        "about the shop.\n");

    sign = "Eril's Armoury\n" +
        "To order a custom piece of armour, simply 'order armour'.\n" +
        "To list other armours and weapons available for sale, 'list'.\n";

    add_item("sign", sign);
    add_cmd_item("sign", "read", sign);

    config_default_trade();
    set_store_room(THIS_DIR + "armoury_store_room");

    add_exit("avenue/ave22", "east");
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
    string type = function_exists("create_object", ob);
    if ((type == ARMOUR_OBJECT) || (type == WEAPON_OBJECT))
    {
        return ::shop_hook_allow_sell(ob);
    }

    notify_fail("This shop specializes in weapons and armours.\n");
    return 0;
}

public int
check_for_eril()
{
    if (!present("eril_the_smith"))
    {
        notify_fail("Nobody is here to help you with that.\n");
        return 0;
    }

    return 1;
}

public int
do_buy(string str)
{
    return (!check_for_eril() ? 0 : ::do_buy(str));
}

public int
do_value(string str)
{
    return (!check_for_eril() ? 0 : ::do_value(str));
}

public int
do_sell(string str)
{
    return (!check_for_eril() ? 0 : ::do_sell(str));
}

public int
do_read(string str)
{
    return 0;
}
