#pragma save_binary

#include "defs.h"
#include <std.h>
#include <macros.h>

inherit "/std/board.c";

void
create_board()
{
    setuid();
    seteuid(getuid());
    
    set_name("board");
    set_short("Beta board");
    set_board_name(ELEMENTALIST_DIR + "beta_board");
    set_num_notes(50);
    set_silent(0);
    set_show_lvl(0);
    set_remove_rank(WIZ_NORMAL);
    set_remove_str("You have to be a wizard to do that!\n");
}

