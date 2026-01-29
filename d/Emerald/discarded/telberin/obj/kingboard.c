/* This is the Royal Proclamations Board for the King of Telberin*/
inherit "std/board";
#include "/d/Emerald/defs.h"
#include <std.h>

void
create_board()
{
    setuid();
    seteuid(getuid());

	set_board_name(TELBERIN_DIR+"royal_board_data");
	set_num_notes(30);
        set_show_lvl(0);
	set_remove_rank(WIZ_NORMAL);
	set_short("Royal Board of Telberin");
}

