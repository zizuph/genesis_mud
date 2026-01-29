#pragma save_binary

#include "default.h"
#include </secure/std.h>
#include <stdproperties.h>

create_room() 
{
	set_short("Anouncement room");
	set_long(
		"Wizard anouncement room.\n" +
		"This board is intended to be used when the someone wants\n" +
		"to put a note for all to see and not scroll off the\n" +
		"normal common board. This could be news about the hunt\n" +
		"for sites. Normal 'hello notes' should be put on the\n" +
		"common board.\n"
	);
	add_exit(THIS_DIR + "tmpc", "east");
	load_board("announce");

    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(ROOM_I_NO_TELEPORT, 1);
}
