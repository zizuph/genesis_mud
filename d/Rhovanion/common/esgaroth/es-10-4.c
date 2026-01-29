inherit "/d/Rhovanion/lib/room";
inherit "/lib/pub";

#include <stdproperties.h>

create_room()
{
    add_exit("/d/Rhovanion/common/esgaroth/es-9-4", "west");
    set_short("Eastern pub");
    set_long("This is the pub of the black dragon, one of two pubs here " +
        "in Esgaroth.  It doesn't seem to get much business.  You can " +
        "leave west back to the street, or stay here and buy yourself a " +
        "drink.  There is a menu with the drinks and their prices on it.\n");

    add_prop(ROOM_I_INSIDE, 1);

    add_drink(({ "beer", "lake beer" }), "beer", "lake", 50, 3, 50, "lake beer",
        "lake beers", "This is a lake beer, from the pub in Esgaroth.  " +
        "It seems rather watery, and you think the name probably comes from " +
        "that.\n");
    add_drink(({ "whiskey", "dock whiskey" }), "whiskey", "dock", 200, 20, 200,
        "dock whiskey", "dock whiskeys", "This is a dock whiskey, the favored drink of many " +
        "sailors and longshoreman.\n");

    add_item("menu", "You could read it to find out what drink so you can " +
        "buy here.\n");
    add_cmd_item("menu", "read", "The sign reads:\n\nWe only have the " +
        "following, since a large sailing ship bought up all our stock " +
        "recently.\n    lake beer    50cc\n    dock whiskey    200cc\n");
}

init()
{
    ::init();
    init_pub();
}
