#pragma save_binary

#include "default.h"
#include </secure/std.h>

create_room() 
{
    object board;

	set_short("Wizard Spell Discussion room");
	set_long(
		"Wizard spell discussion room.\n" +
		"This is a room for discussions and planning magic.\n" +
		"To the west is the general discussion room.\n"
	);
	add_exit(THIS_DIR + "discuss", "west");
	board = load_board("magic");
    board->set_num_notes(50);

	add_default_exits();
}
