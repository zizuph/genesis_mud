#pragma strict_types

inherit "/std/board";

#include <std.h>
#include "defs.h"

public void
create_board()
{
    set_short("obsidian board");
    set_board_name(PRIVATE_BOARD);
    set_num_notes(30);
    set_silent(0);
    set_show_lvl(1);
    set_remove_rank(WIZ_NORMAL);
    set_remove_str("Only wizards can do that.");
    set_keep_discarded(1);
}
