/*
 *  coded by Amelia for Ten Alders 4/13/97
*/

#pragma no_clone
#pragma strict_types

inherit "/d/Earthsea/std/room";
inherit "/d/Emerald/lib/shop_list";

#include <stdproperties.h>

public void
create_earthsea_room()
{
    object door;
    config_default_trade();
    set_money_greed_sell(95);
    set_money_greed_buy(95);
    set_store_room("/d/Earthsea/gont/tenalders/village/peddler_store");
    set_short("Peddler shop");
    set_long("This looks like a peddler's shop. You see piles " +
        "of wares heaped on the floor and against the wall. You can " +
        "<buy> or <sell> loot from your journeys here. Also, you can " +
        "<list> equipment, armours, or weapons to see what the peddler " +
        "has in stock.\n");
    add_item((({"wares", "piles of wares"})),
        "All sorts of used junk that the peddler buys and " +
        "resells.\n");
    add_prop(ROOM_I_INSIDE, 1);
    reset_room();
    door = clone_object("/d/Earthsea/gont/tenalders/obj/doors/peddler_in");
    door->move(this_object());
}

public void
init()
{
    ::init();
    init_shop();
}
