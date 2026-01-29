
#pragma save_binary

inherit "std/board.c";
#include "defs.h"
#include <std.h>
#include <macros.h>
#include COUNCIL_HEADER

void
create_board()
{
    seteuid(getuid(THIS));
    set_name("board");
    set_short("Elemental Worshippers of Calia Granted Members bulletin board");
    set_board_name(WOR_TEMPLE+"granted");
    set_num_notes(30);
    set_silent(0);
    set_show_lvl(0);
    set_remove_rank(WIZ_NORMAL);
    set_remove_str("You have to be a wizard to do that!\n");
}

int
allow_remove()
{
    return (COUNCIL_CODE->is_council_member(TP->query_real_name()));
}
