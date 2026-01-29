#pragma save_binary

#include "defs.h"
#include <std.h>
#include <macros.h>

inherit "/std/board.c";

#include WORSHIP_HEADER
#include COUNCIL_HEADER

void
create_board()
{
    seteuid(getuid(THIS));
    set_name("board");
    set_short("Elemental Guild Recode discussion board");
    set_board_name(WOR_TEMPLE+"discuss_board");
    set_num_notes(50);
    set_silent(0);
    set_show_lvl(0);
    set_remove_rank(WIZ_NORMAL);
    set_remove_str("You have to be a wizard to do that!\n");
}

