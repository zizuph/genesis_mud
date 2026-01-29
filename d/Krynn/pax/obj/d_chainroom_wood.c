#include "/d/Krynn/common/defs.h"
#include "../local.h"
inherit STDDOOR;

create_door()
{
    set_pass_command(({"s", "south"}));
    set_door_name(({"wooden door", "door", "south door"}));
    set_other_room(PSLA+ "final_tunnel01");
    set_door_desc(BS("It is a huge door made of wood. It looks quite " +
	"tough and will probably not break if you tries to kick it in. But " +
	"there is a lock in the door.", 70));
    set_open(0);
    set_locked(1);
    set_lock_command("lock");
    set_lock_name("lock");
    set_lock_desc("It's a small lock made of silver.\n");
    set_unlock_command("unlock");
    set_open_desc("");
    set_closed_desc("");
}
