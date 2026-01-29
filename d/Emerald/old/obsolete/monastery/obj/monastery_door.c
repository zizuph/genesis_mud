#include "/d/Emerald/sys/paths.h"

inherit EMERALD_DOOR_OBJ;

#include "../defs.h"

void
create_emerald_door()
{
    set_door_name(({"oak door","door"}));
    set_unlock_command("unlock");
    set_lock_command("lock");
    set_open(0);
    set_locked(1);
}
