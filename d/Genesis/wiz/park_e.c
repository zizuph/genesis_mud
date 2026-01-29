#pragma save_binary

#include <stdproperties.h>
#include "default.h"

create_room() 
{
	set_short("The island park");
	set_long(
		"You stand in the beautiful park.\n" +
		"The grass under your feet is soft and comfortable.\n" +
		"To the west you can see midpoint of the island.\n" +
		"To the east you can see a bridge connecting to another island.\n"
	);
	add_exit(THIS_DIR + "green", "west");
	add_exit(THIS_DIR + "bridge", "east");
	change_prop(ROOM_I_LIGHT, 10);
}