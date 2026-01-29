

#pragma save_binary

inherit "/std/board.c";
#include "defs.h"
#include <std.h>
#include <macros.h>
#include COUNCIL_HEADER

void
create_board()
{
    seteuid(getuid());
    set_name("board");
    set_short("board of the Spirit Circle Council");
    set_board_name("/d/Calia/private/scop/council_msgs");
    set_num_notes(30);
    set_silent(0);
    set_show_lvl(0);
    set_remove_rank(WIZ_ARCH);
    set_remove_str("You can't do that.\n");
}

int
council_board_check()
{
    return (COUNCIL_CODE->is_council_member(capitalize(TP->query_real_name()))
        || COUNCIL_CODE->is_calian_wiz(TP) || (WIZ_CHECK >= WIZ_ARCH));
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

