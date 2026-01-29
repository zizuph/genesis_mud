#include "/d/Krynn/common/defs.h"
#include "../local.h"
inherit STDDOOR;

create_door()
{
    set_pass_command(({"w", "west"}));
    set_door_name(({"green door", "door"}));
    set_door_desc("It is a normal green wooden door, there is small " +
		  "sign on it.\n");
    add_item("sign", "There are some writting on it.\n");
    add_cmd_item(({"sign", "writting"}), "read", "It says:\n  Tika Waylan\n");
    set_other_room(HOUSE + "tika");
    set_open(0);
    set_open_desc("");
    set_closed_desc("");
}
