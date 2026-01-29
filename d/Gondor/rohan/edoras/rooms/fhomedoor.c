inherit "/std/door";
#include "/d/Gondor/defs.h"

public void
create_door()
{
    ::create_door();
    set_door_id("path8_south");
    set_pass_command(({"n","north"}));
    set_door_name(({"wooden door","door"}));
    set_other_room(EDORAS_DIR + "path8.c");
    set_lock_command("lock");
    set_lock_name("lock");
    set_unlock_command("unlock");
    set_open(0);
    set_locked(1);
    set_no_pick();
    set_key("_funoheds_home_key");
}
