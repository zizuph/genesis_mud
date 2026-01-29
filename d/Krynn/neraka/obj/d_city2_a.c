/* A door in Neraka coded by Nick */

#include "/d/Krynn/common/defs.h"
#include "../local.h"
inherit "/std/door";

create_door()
{
    ::create_door();

    set_door_id("grate_2");
    set_pass_command(({"d", "down"}));
    set_door_name(({"steel grate", "grate"}));
    set_other_room(TDIR + "hole2");
    set_lock_command("lock");
    set_lock_name("lock");
    set_unlock_command("unlock");
    set_open(0);
    set_locked(0);
}
