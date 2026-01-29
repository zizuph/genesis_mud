#include "/d/Krynn/common/defs.h"
#include "../local.h"
inherit STDDOOR;

create_door()
{
    set_pass_command(({"w", "west"}));
    set_name(({"brown door", "door"}));
    set_long("It is a normal brown wooden door, leading to the " +
	     "outside world.\n");

    set_other_room(TDIR + "bridge_walk10");
    set_open(0);
    set_open_desc("");
    set_closed_desc("");
}
