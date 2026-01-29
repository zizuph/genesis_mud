inherit "/std/door";

#include "/d/Roke/common/defs.h"

create_door()
{
    set_door_id("wood_door_2");

    set_pass_command(({"e","east"}));

    set_door_name(({"iron door","door"}));

    set_other_room(CELL_D+"secret_study");

    set_lock_command("lock");
    set_lock_name("lock");
    set_unlock_command("unlock");

    set_open(0);
    set_locked(1);

}
