#pragma save_binary

#include <stdproperties.h>
#include "default.h"

create_room()
{
	set_short("The wiz-tool room");
	set_long(
		"This room is for discussions about various wiz tools .\n"  +
		"To the south is the room for LPC discussions.\n"
	);
	add_exit(THIS_DIR + "lpc", "south");
	add_default_exits();
	change_prop(ROOM_I_LIGHT, 10);
	load_board("tools");
}