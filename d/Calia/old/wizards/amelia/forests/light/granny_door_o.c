inherit "/std/door";
#include "defs.h"

void create_door()
	{
	set_other_room(FPATH+"cottage1");
	set_door_id("wooden dutch door");
	set_door_desc("A wooden dutch door, divided in two parts.\n");
	set_door_name(({"door", "wooden dutch door", "dutch door"}));
	set_pass_command(({"e","east"}));
	set_open(0);
	}
