
#pragma save_binary

inherit "std/board.c";
#include <std.h>
#include <macros.h>

void
create_board()
{
    seteuid(getuid(this_object()));
    set_name("board");
    set_short("Calian Domain board");
    set_board_name("/d/Calia/log/board_data");
    set_num_notes(30);
    set_silent(0);
    set_show_lvl(0);
    set_remove_rank(WIZ_NORMAL);
    set_remove_str("You have to be a wizard to do that!\n");
}

