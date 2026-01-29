#include "/d/Krynn/common/defs.h"
#include "../local.h"
inherit STDDOOR;

create_door()
{
    set_pass_command(({"e", "east"}));
    set_door_name(({"bronze door", "door"}));
    set_door_desc(BS("It is a huge door made of solid bronze. You can " +
		"see a lock in the door.", 70));
    set_other_room(PSLA+ "tomb04");
    set_open(0);
    set_locked(1);
    set_pick(40+random(20));
    set_open_desc("");
    set_closed_desc("");

    set_lock_command("lock");
    set_lock_name("lock");
    set_lock_desc("It's a rather big lock.\n");
    set_unlock_command("unlock");
}
