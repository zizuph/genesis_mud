#include "/d/Krynn/icewall/local.h"
inherit "/std/door";

create_door()
{
    ::create_door();

    set_door_id("celldoor");
	set_pass_command(({"w", "west"}));
    set_door_name(({"cell door", "door", "wooden door"}));
    set_other_room(BASE + "prisons.c");
    set_lock_command("lock");
    set_lock_name("lock");
    set_lock_desc("It's a small rusty but usable lock.\n");
    set_unlock_command("unlock");
    set_open(0);
    set_locked(0);
}
