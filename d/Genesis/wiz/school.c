#pragma save_binary

#include <stdproperties.h>
#include "default.h"

create_room()
{
	set_short("The island of development and education");
	set_long(
		"This is the entrance to the educational area.\n" +
		"In the northern building are the bulletin boards for discussions\n" +
		"regarding programming and wiztools.\n" +
		"The bridge is to the west of here.\n"
	);
	add_exit(THIS_DIR + "lpc", "north");
	add_exit(THIS_DIR + "bridge", "west");
	add_exit(THIS_DIR + "intro", "east", "@@construction");
	change_prop(ROOM_I_LIGHT, 10);
}