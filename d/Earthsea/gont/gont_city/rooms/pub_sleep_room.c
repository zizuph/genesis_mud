#pragma strict_types
#pragma no_clone

inherit "/std/room";

#include <macros.h>
#include <stdproperties.h>

public void
create_room()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    set_short("Bedroom");
    set_long("This is a small yet comfortable "+
        "bedroom where customers from the pub can sleep it off. "+
        "If you have the key, you may <start here> to begin "+
        "your travels here next time you wake in these realms.\n");
    add_exit("tavern", "south");
    add_prop(ROOM_I_INSIDE, 1);
}

public int
start_here(string str)
{
    object tp = this_player(), key;

    if(str == "here")
    {
        key = present("_overnight_key_", tp);

        if(!key->query_overnight())
        {
            write("You do not have the key to the room!\n");
            return 1;
        }

        write("You turn the key in the lock.\nOk, you will wake " +
            "here next time you log in.\n");
        key->remove_object();
        tp->set_temp_start_location(MASTER_OB(this_object()));
        return 1;
    }

    return notify_fail("Start where?\n");
}

public void
init()
{
    ::init();
    add_action(start_here, "start");
}
