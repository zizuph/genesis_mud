/*
 * /d/Gondor/private/boards/gondorprivate.c
 *
 * Private board for Gondorian wizards.
 *
 * Mercade, Februari 17 2000
 */

inherit "/std/board";

#include <std.h>

void
create_board()
{
    set_name("worksheet");
    add_name("board");
    set_short("worksheet for Gondorian wizards");

    set_board_name("/d/Gondor/private/boards/gondorprivate");
    set_num_notes(50);
    set_silent(0);
    set_show_lvl(1);
    set_remove_rank(WIZ_LORD);
    set_remove_str("You are not permitted to remove that note.\n");
}

int
block_reader()
{
    return 1;
}

int
block_writer()
{
    return 1;
}
