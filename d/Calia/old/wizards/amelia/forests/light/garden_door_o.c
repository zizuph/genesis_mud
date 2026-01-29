inherit "/std/door";
#include "defs.h"

void create_door()
	{
	set_other_room(FPATH+"cottage2");
	set_door_id("wooden dutch door");
	set_door_desc("A wooden dutch door, divided in two parts.\n");
	set_door_name(({"door", "wooden dutch door", "dutch door"}));
	set_pass_command(({"w", "west"}));
	set_open(0);
	set_locked(0);
	}
