#include <stdproperties.h>
#include "default.h"

create_room()
{
	set_short("The LPC room");
	set_long(
		"This room is for discussions about the LPC language.\n"  +
		"To the south you can see the school island entrance.\n" +
		"To the north is the room for wiz tools.\n"
	);
	add_exit(THIS_DIR + "school", "south");
	add_default_exits();
	change_prop(ROOM_I_LIGHT, 10);
	load_board("LPC");
}
