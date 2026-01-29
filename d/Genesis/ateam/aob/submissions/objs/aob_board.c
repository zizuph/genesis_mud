#pragma save_binary

#include <std.h>
#include <macros.h>

inherit "/std/board.c";

void
create_board()
{
    setuid();
    seteuid(getuid());

    set_name("board");
    set_short("Balance Review Submission Board");
    set_board_name("/d/Genesis/ateam/aob/submissions/notes");
    set_num_notes(50);
    set_silent(0);
    set_show_lvl(1);
    set_remove_rank(WIZ_NORMAL);
    set_remove_str("You have to be a wizard to do that!\n");
}

int
block_reader(int note)
{
    return 1;
}
