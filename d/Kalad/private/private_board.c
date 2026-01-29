#pragma save_binary
#pragma strict_types
inherit "/std/board";
#include <std.h>

void
create_board()
{
    set_board_name("/d/Kalad/private/private_board_data");
    set_num_notes(35);
    set_silent(0);
    set_show_lvl(1);
    set_remove_rank(WIZ_NORMAL);
    set_remove_str("You are not allowed to remove that note.\n");
}

int
block_reader()
{
    if(this_player()->query_real_name() == "decius")
         return 0;
    return 1;
}
