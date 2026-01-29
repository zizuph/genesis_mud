#pragma save_binary

inherit "/std/board";

#include <std.h>

void
create_board()
{
    set_board_name("/d/Genesis/wiz/boards/admin");
    set_num_notes(30);
    set_show_lvl(1);
    set_remove_rank(WIZ_ARCH);
    set_remove_str("Only an Archwizard or Keeper can do that.");
}

int block_writer() { return 1; }
