/* This is the board in the boardroom,
 * modified by Teth, Dec 7 1996, for new VK (in board_office.)
 */

#include <std.h>

inherit "/std/board";

public void
create_board()
{
    set_board_name("/d/Krynn/belize/hall/bboard.c");
    set_num_notes(25);
    set_silent(0);
    set_show_lvl(10);
    set_remove_rank(WIZ_MAGE);
    set_remove_str("Sorry, only certain wizards may remove notes.\n");
}

