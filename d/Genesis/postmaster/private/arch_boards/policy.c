inherit "/std/board";

#include <std.h>

void
create_board()
{
    set_board_name("/d/Genesis/postmaster/private/arch_boards/policy");
    set_num_notes(100);
    set_show_lvl(1);
    set_remove_rank(WIZ_LORD);
    set_remove_str("Only an Archwizard, Keeper or Liege can do that.");
}

int
block_reader()
{
    return (SECURITY->query_wiz_rank(geteuid(this_interactive())) < WIZ_LORD);
}

int
block_writer()
{
    return block_reader();
}
