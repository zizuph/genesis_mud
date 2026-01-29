/*
 * A normal board.
 * To be used by all members of the High Sorcery!
 *
 * 950601 by Rastlin
 */

#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <std.h>

inherit "/std/board";

void
create_board()
{
    seteuid(getuid(TO));

    set_board_name(NORMAL_BOARD);
    set_num_notes(30);
    set_silent(0);
    set_show_lvl(1);
    set_remove_rank(WIZ_MAGE);
    set_remove_str("Only a Mage or higher may remove the notes!\n");
    set_no_report(0);
    set_keep_discarded(0);
}
