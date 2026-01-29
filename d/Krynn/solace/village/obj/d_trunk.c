#include "/d/Krynn/common/defs.h"
#include "../local.h"
inherit "/std/door";

create_door()
{
    ::create_door();

    set_door_id("door_trunk");
    set_pass_command(({"out", "leave", "enter"}));
    set_door_name(({"wooden door", "door"}));
    set_door_desc("A sturdy looking wooden door.\n");
    set_open_desc("There is a wooden door leading out from the tree here.\n");
    set_closed_desc("A closed door is here.\n");
    set_other_room(TDIR + "solace13");
    set_lock_command("lock");
    set_lock_name("lock");
    set_unlock_command("unlock");
    set_open(0);
    set_locked(1);
    set_pick(20);
}

