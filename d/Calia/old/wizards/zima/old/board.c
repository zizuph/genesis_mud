inherit "std/board.c";
#include "defs.h"

create_board()
{
    seteuid(getuid(THIS));
    set_name("board");
    set_short("Zima's test board");
    set_board_name("/d/Dville/zima/bull_board");
    set_num_notes(30);
    set_anonymous(0);
    set_silent(0);
    set_show_lvl(0);
    set_remove_lvl(1);
    set_remove_str("You have to be a wizard to do that!\n");
}
