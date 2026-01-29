#pragma save_binary
#pragma strict_types
inherit "/std/board";
#include <std.h>

void
create_board()
{
    set_board_name("/d/Raumdor/log/drakmere_board_data");
    set_num_notes(100);
    set_silent(0);
    set_show_lvl(1);
    set_remove_rank(WIZ_NORMAL);
    set_remove_str("You are not allowed to remove that note.\n");
}
