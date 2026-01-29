inherit "/d/Rhovanion/lib/room";
inherit "/d/Emerald/common/shop_list";

#include <stdproperties.h>

create_room()
{
    set_store_room("/d/Rhovanion/common/esgaroth/es-5-11");
    set_short("Town shop");
    set_long("This is the town shop, where people come to buy and " +
        "sell goods, or just to gawk at the travellers and their " +
        "items.  There is a sign on the wall that the owner put up " +
        "so that he wouldn't have to answer your questions.  You " +
        "should read it if you need help.  There is a small " +
        "staircase leading upwards here also.\n");

    add_exit("/d/Rhovanion/common/esgaroth/es-6-12", "east");
    add_exit("/d/Rhovanion/common/esgaroth/es-5-11", "north", "@@wiz_check");
    add_exit("/d/Rhovanion/common/esgaroth/es-5-12-up", "up");
    add_prop(ROOM_I_INSIDE, 1);
    config_default_trade();
}

init()
{
    ::init();
    init_shop();
}
