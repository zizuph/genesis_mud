inherit "/std/door";
#include "/d/Gondor/defs.h"

create_door()
{
    ::create_door();
    set_door_id("councildoor");
    set_pass_command(({"n","north"}));
    set_door_name(({"oaken door","door"}));
    set_other_room(RANGER_NORTH_DIR+"s_corridor");
    set_door_desc("A sturdy oaken door.\n");
    set_lock_command("lock");
    set_lock_name("lock");
    set_unlock_command("unlock");
    set_open(0);
    set_locked(1);
    set_key("Captain_Key");
    set_knock_command("knock");
}

int
open_door(string arg)
{
    if (query_locked())
    {
        if (!(unlock_door(arg + " with silver key")))
        {
            return 0;
        }
        write("You decide to unlock the door before opening it.\n");
    }

    return (::open_door(arg));
}

int
close_door(string arg)
{
    if (!(::close_door(arg)))
    {
        return 0;
    }

    write("After you close the door you decide to lock it as well.\n");
    return (lock_door(arg + " with silver key"));
}

