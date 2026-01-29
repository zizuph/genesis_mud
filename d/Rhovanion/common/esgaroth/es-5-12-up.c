inherit "/d/Rhovanion/lib/room";
inherit "/d/Emerald/common/shop_list";

#include <stdproperties.h>

create_room()
{
    set_store_room("/d/Rhovanion/common/esgaroth/es-5-11-up");
    set_short("Special purchases");
    set_long("The proprietor of this shop recently tooks some " +
        "journeys to other lands, and was so impressed with some " +
        "of their wares that he opened up this shop and began " +
        "to import them.\n");

    add_exit("/d/Rhovanion/common/esgaroth/es-5-12", "down");
    add_prop(ROOM_I_INSIDE, 1);
    config_default_trade();
}

init()
{
    ::init();
    add_action("do_buy", "buy");
    add_action("do_sell", "sell");
    add_action("do_value", "value");
    add_action("do_list", "list");
    add_action("do_read", "read");
}

public int
do_sell(object ob)
{
    write("Sorry, we don't buy things here.\n");
    return 1;
}
