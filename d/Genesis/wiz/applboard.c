#pragma save_binary

inherit "/std/board";
#include <std.h>

create_board()
{
    set_board_name("/d/Genesis/wiz/boards/application");
    set_name(({ "board", "application board" }));
    set_num_notes(200);
    set_silent(1);
    set_remove_rank(WIZ_ARCH);
    set_remove_str("Only an Archwizard or Keeper can do that");
}

int block_reader() { return 1; }
