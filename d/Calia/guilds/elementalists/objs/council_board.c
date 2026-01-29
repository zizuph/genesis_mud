

#pragma save_binary

inherit "std/board.c";
#include "defs.h"
#include <std.h>
#include <macros.h>

void
create_board()
{
    seteuid(getuid(THIS));
    set_name("board");
    set_short("board of the Elemental Worshippers Council");
    set_board_name("/d/Calia/private/worship_council/council_msgs");
    set_num_notes(30);
    set_silent(0);
    set_show_lvl(0);
    set_remove_rank(WIZ_ARCH);
    set_remove_str("You can't do that.\n");
}

int
council_board_check()
{
    object tp = TP;
    return GUILD_MANAGER->query_is_ew_council(tp, 1);

}


/* Stop unwanted people reading, writing or removing notes */
varargs int block_reader()
{
    return !council_board_check();
}


varargs int allow_remove()
{
    return council_board_check();
}


varargs int block_writer()
{
    return !council_board_check();
}

