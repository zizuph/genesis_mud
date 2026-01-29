#pragma save_binary
inherit "/std/board.c";

#include <std.h>

public void
create_board()
{
    seteuid(getuid(this_object()));
    set_short("The Wisdom Board of Terel");
    set_board_name("/d/Terel/common/board");
    set_num_notes(30);
/*    set_anonymous(0);  Not in use... Mortricia May 1996 */
    set_silent(0);
    set_show_lvl(1);
    set_remove_rank(WIZ_NORMAL);
    set_remove_str("You have no such power.\n");
}
