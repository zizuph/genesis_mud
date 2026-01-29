/* A door in Neraka coded by Nick */

#include "/d/Krynn/common/defs.h"
#include "../local.h"
inherit "/std/door";

create_door()
{
    ::create_door();

    set_door_id("door_1");
    set_pass_command(({"s", "south"}));
    set_door_name(({"bronze door", "door"}));
    set_other_room(TDIR + "city1");
    set_lock_command("lock");
    set_lock_name("lock");
    set_unlock_command("unlock");
    set_open(0);
    set_locked(1);
}
