inherit "/std/board";
#include <std.h>

create_board()
{
	seteuid(getuid(this_object()));
	add_name("board");
	set_short("board");
	set_board_name("/d/Avenir/common/bazaar/board_data");
	set_num_notes(30);
//      set_anonymous(0);
	set_silent(0);
	set_show_lvl(0);
//      set_remove_lvl(30);
	set_remove_str("Only Lords and above can remove notes.\n");
}
