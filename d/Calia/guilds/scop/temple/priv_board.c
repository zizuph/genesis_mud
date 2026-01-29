
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
    set_name("tome");
    set_short("enormous gilded tome");
    add_adj(({"enormous","gilded"}));
    set_board_name(SPIRIT_TEMPLE+"board");
    set_num_notes(50);
    set_silent(0);
    set_show_lvl(0);
    set_no_show_composite(1);
    set_remove_rank(WIZ_NORMAL);
    set_remove_str("You have to be a wizard to do that!\n");
}

int
allow_remove()
{
    return (COUNCIL_CODE->is_council_member(TP->query_real_name()));
}
