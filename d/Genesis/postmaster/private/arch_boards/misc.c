inherit "/std/board";

#include <std.h>

void
create_board()
{
    set_board_name("/d/Genesis/postmaster/private/arch_boards/misc");
    set_num_notes(50);
    set_show_lvl(1);
    set_remove_rank(WIZ_ARCH);
    set_remove_str("Only an Archwizard or Keeper can do that.");
}

int block_reader() { return 1; }
int block_writer() { return 1; }
