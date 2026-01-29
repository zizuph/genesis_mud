#pragma save_binary

#include "default.h"
#include <std.h>

void
create_room() 
{
	set_short("Wizard Idea room");
	set_long(
		"Wizard Idea room.\n" +
		"This is a room for inventive ideas.\n" +
		"Please note: Only ideas here! " +
		     "Follow up and discussions on the discuss board!\n" +
		"To the west is the lounge.\n"
	);
	add_exit(THIS_DIR + "lounge", "west");
	add_default_exits();
        clone_object(THIS_DIR + "ideaboard")->move(this_object(), 1);
}
