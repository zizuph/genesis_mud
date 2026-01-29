/*
 * A normal board.
 * To be used by all members of the High Sorcery!
 *
 * 950601 by Rastlin
 */

#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include "/d/Krynn/guilds/wohs/defs.h"
#include <std.h>

inherit "/std/board";

void
create_board()
{
    seteuid(getuid(TO));

    set_board_name(NORMAL_BOARD);
    set_num_notes(50);
    set_silent(0);
    set_show_lvl(1);
    set_remove_str("Only a member of the Conclave can remove notes.\n");
    set_no_report(0);
    set_keep_discarded(0);
}

public varargs int
allow_remove(int note)
{
    if(QUERY_WHITE_COUNCIL(TP) || QUERY_RED_COUNCIL(TP) || QUERY_BLACK_COUNCIL(TP))
        return 1;

    return 0;
}