#include "/d/Krynn/common/defs.h"
#include "../local.h"
inherit STDDOOR;

create_door()
{
    set_pass_command(({"w", "west"}));
    set_door_name(({"bronze door", "door", "west door"}));
    set_other_room(PSLA+ "hall_col01");
    set_door_desc(BS("It is a huge door made of solid bronze. The door " +
		"bear a raised outline of Pax Tharkas, done in considerable " +
		"detail. You can also see a lock in the door.", 70));
    set_open(0);
    set_locked(1);
    set_pick(40+random(20));
    set_lock_command("lock");
    set_lock_name("lock");
    set_lock_desc("It's a rather big lock.\n");
    set_unlock_command("unlock");
    set_open_desc("");
    set_closed_desc("");
}
