/*
 * changed greediness to 90, to fix bug
 */

#pragma strict_types
#pragma no_clone

inherit "/std/room";
inherit "/d/Emerald/lib/shop_list";

#include <stdproperties.h>

#define STORE "/d/Earthsea/gont/gont_city/rooms/general_store"

public void
create_room()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    config_default_trade();
    set_money_greed_sell(95);
    set_money_greed_buy(95);
    set_store_room(STORE);
    set_short("General store");
    set_long("You see stacks of "+
        "all sorts of used equipment "+
        "and other articles for sale around the store. Here you can "+
        "<buy> or <sell> used equipment, armour, weapons, or other "+
        "items of value. You can also ask to <list> equipment, "+
        "armour, or weapons.\n");
    add_exit("city_street/city_road3", "north");
    add_prop(ROOM_I_INSIDE, 1);
}

public void
init()
{
    ::init();
    init_shop();
}
