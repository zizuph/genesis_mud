#include "/d/Krynn/icewall/local.h"
inherit "/std/door";

create_door()
{
    ::create_door();

    set_door_id("masdoor");
    set_pass_command(({"w", "west"}));
    set_door_name(({"pair of engraved double doors", "doors", "engraved double doors"}));
    set_other_room(ICE_CAST2_R + "hall4_2.c");
    set_lock_command("lock");
    set_lock_name("lock");
    set_lock_desc("It's a clean lock.\n");
    set_unlock_command("unlock");
    set_open(0);
    set_locked(1);
}
