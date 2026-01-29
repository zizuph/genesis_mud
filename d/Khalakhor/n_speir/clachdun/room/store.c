#include "local.h"

inherit BUILDING_BASE;
inherit "/lib/shop";

void
create_building()
{
    set_up_cords(6,12);
    set_store_room(ROOM_DIR + "storeroom");
    config_default_trade();
    set_money_give_max(1000);
    set_money_give_out(({1000, 700, 40, 1}));
    set_money_give_reduce(({0,7,4,1}));
    add_exit(ROOM_DIR + "building_5_12", "west");
}

void
init()
{
    ::init();
    init_shop();
}
