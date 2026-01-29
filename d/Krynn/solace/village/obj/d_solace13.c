/* A door in Solace, coded by Nick */

inherit "/std/door";
#include "/d/Krynn/common/defs.h"
#include "../local.h"

create_door()
{
    ::create_door();

    set_door_id("door_trunk");
    set_pass_command(({"enter", "go"}));
    set_door_name(({"wooden door", "door"}));
    set_door_desc("A sturdy looking wooden door.\n");
    set_open_desc("");
    set_closed_desc("");
    set_other_room(TDIR + "trunk");
    set_lock_command("lock");
    set_lock_name("lock");
    set_unlock_command("unlock");
    set_open(0);
    set_locked(1);
    set_pick(20);
}

