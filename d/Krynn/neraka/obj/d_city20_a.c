/* A door in Neraka coded by Nick */

#include "/d/Krynn/common/defs.h"
#include "../local.h"
inherit "/std/door";

create_door()
{
    ::create_door();

    set_door_id("grate_20");
    set_pass_command(({"d", "down"}));
    set_door_name(({"rusty steel grate", "grate", "steel grate"}));
    set_other_room(TDIR + "hole20");
    set_lock_command("lock");
    set_lock_name("lock");
    set_unlock_command("unlock");
    set_open(0);
    set_locked(1);
    set_pick(60);
}
