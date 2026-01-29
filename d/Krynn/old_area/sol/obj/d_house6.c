#include "/d/Krynn/common/defs.h"
#include "../local.h"
inherit STDDOOR;

create_door()
{
    set_pass_command(({"n", "north"}));
    set_name(({"green door", "door"}));
    set_long("It is a normal green wooden door, leading to the " +
	     "outside world.\n");

    set_other_room(TDIR + "bridge_walk26");
    set_open(0);
    set_open_desc("");
    set_closed_desc("");
}
