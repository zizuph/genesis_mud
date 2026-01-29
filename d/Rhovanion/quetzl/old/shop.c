inherit "/std/room";

inherit "/d/Immortal/quetzl/test_output";

#include <stdproperties.h>

public void
create_room()
{
    set_short("Market Emporium");
    set_long("You have entered the Cove market emporium where you can buy " +
        "and sell general items of interest. There is a sign on the wall " +
        "that explains how to use the store. Many times adventurers sell " +
        "their items on their way to exchange wondrous tales at the " +
        "Traveller guild.\n");
    add_prop(ROOM_I_INSIDE, 1);
    add_exit("/d/Roke/varl/atuan/cape/cove4", "north");
    add_exit("/d/Roke/varl/atuan/cape/hshop", "west");

    set_store_room("/d/Roke/varl/atuan/cape/store");
    default_config_trade();
}

public void
init()
{
    ::init();
    init_shop();
}
