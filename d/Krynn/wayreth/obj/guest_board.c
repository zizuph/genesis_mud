/*
 * A guest board.
 * To be used by visitors to the Wizards the High Sorcery
 *
 * Arman 2017
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

    set_short("notice board");
    add_name("board");
    set_long("A small board has been attached to one of the walls here for guests " +
        "and aspirants to pin notes.\n");
    set_board_name(GUEST_BOARD);
    set_num_notes(50);
    set_silent(0);
    set_no_report(0);
    set_keep_discarded(0);
}
