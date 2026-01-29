inherit "/std/door";

#include "/d/Roke/common/defs.h"

create_door()
{
    set_door_id("stone_door");

    set_pass_command(({"s","south"}));

    set_door_name(({"stone door","door"}));

    set_other_room(CELL_D+"ghoul_room");

    set_lock_command("lock");
    set_lock_name("lock");
    set_unlock_command("unlock");

    set_open(0);
    set_locked(1);

}
