#pragma save_binary

#include <stdproperties.h>
#include "default.h"

create_room() 
{
	object bull_board;
	set_short("Entrance of the wizard club");
	set_long( break_string(
		"Welcome to the wizard club! " +
		"Please refrain from inviting mortals as this will " +
		"ruin the atmosphere of the game for them " +
		"and may irritate fellow wizards. " +
		"To the north is the center of wizards isle, " +
		"east of here is a branch of the post office, " +
		"west is the common meeting area of Genesis, " +
		"south is the lounge area for relaxing and socializing. " +
		"The bulletin board is meant for important announcements!\n"
		, 78, 0)
	);
	add_exit(THIS_DIR + "green", "north");
	add_exit(THIS_DIR + "post", "east");
	add_exit(THIS_DIR + "com", "west");
	add_exit(THIS_DIR + "lounge", "south");
	change_prop(ROOM_I_LIGHT, 10);
	add_default_exits();
	bull_board = load_board("news");
	bull_board->set_keep_discarded(1);
	bull_board->set_num_notes(99);
}
