#pragma save_binary

#include <stdproperties.h>
#include "default.h"

create_room()
{
	set_short("The bridge");
	set_long(
		"You are standing on the bridge connecting the main island\n" +
		"and the development and education island.\n" +
		"Below, you can see the whole world of Genesis.\n"
	);
	add_exit(THIS_DIR + "park_e", "west");
	add_exit(THIS_DIR + "school", "east");
	change_prop(ROOM_I_LIGHT, 10);
}
