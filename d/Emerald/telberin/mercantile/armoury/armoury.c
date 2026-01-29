#include "../../defs.h"

inherit TELBERIN_BUILDING;
inherit "/d/Emerald/lib/shop_list";

#include <stdproperties.h>
#include <files.h>

void
create_telberin_building()
{
    string sign;

    set_short("Eril's armoury");
    set_em_long("You are in the shop of the famous elven smith, Eril.  " +
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

    sign = "Welcome to Eril's Armoury!\n\n"
         + "If the armourer is here, you may order a custom piece of"
         + " armour with <order armour>. You may also <list> what"
         + " armours are currently for sale.\n";

    add_item("sign", sign);
    add_cmd_item("sign", "read", sign);

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_S_EXIT_FROM_DESC, "from inside the armoury.");

    add_exit(TELBERIN_DIR + "artisans_plaza", "south", 0, 0, 1);

    config_default_trade();
    set_store_room(TELBERIN_MERCANTILE_DIR + "armoury/armoury_store_room");

    reset_room();
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

public mixed
query_location_ids()
{
    return ({ "[the] 'arms' 'shop'",
              "[the] 'armourer'",
              "[the] 'armoury'", });
}

public mixed
query_location_closed()
{
    return 0;
}

public mixed
query_location_desc()
{
    return "An armoury.\n";
}

public string
query_entry_desc()
{
    return "into the armoury";
}
