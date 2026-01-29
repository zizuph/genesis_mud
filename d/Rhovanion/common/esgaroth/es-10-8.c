inherit "/d/Rhovanion/lib/room";
inherit "/lib/trade";

#include <stdproperties.h>
#include <macros.h>

create_room()
{
    config_default_trade();
    set_short("Inn of the Lake");
    set_long("This is the inn of the lake, where you can rent a room for " +
        "the night if you want to stay in esgaroth.  You can leave west " +
        "back out to the street, but why not take a load off of your feet " +
        "and sleep a while?  It will only cost you five silver to do so, " +
        "but once you do, there is not a chance to change your mind.\n");
    add_prop(ROOM_I_INSIDE, 1);
    add_exit("/d/Rhovanion/common/esgaroth/es-9-8", "west");
}

init()
{
    ::init();
    add_action("rent_a_room", "rent");
}

int rent_a_room(string arg)
{
    notify_fail("Rent what?\n");
    if (arg != "room")
        return 0;

    notify_fail("But you can't pay the price!\n");
    if (!can_pay(60, this_player()))
        return 0;

    if (this_player()->set_temp_start_location(MASTER))
    {
        write("You rent a room, and go to sleep for the night.\n");
        pay(60);
        this_player()->command("quit");
        return 1;
    }
    notify_fail("It seems the inn isn't open to guests yet.\n");
    return 0;
}
