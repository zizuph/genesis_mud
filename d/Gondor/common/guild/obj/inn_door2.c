#pragma save_binary

inherit "/std/door";

#include "/d/Gondor/defs.h"

public void
create_door()
{
    ::create_door();

    set_door_id("inndoor");
    set_pass_command(({"n","north"}));
    set_door_name(({"wooden door","door"}));
    set_other_room(RANGER_GON_DIR + "wcorr");
    set_lock_command("lock");
    set_lock_name("lock");
    set_unlock_command("unlock");
    set_pick(40);
    set_open(0);
    set_locked(0);
    set_knock_command("knock");
}
