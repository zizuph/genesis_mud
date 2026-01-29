/*
 * External Board
 *
 * This one is free to use for all players of Genesis
 */
inherit "/std/board";

#include <macros.h>
#include <std.h>

#include "actor.h"

public nomask void
create_board()
{
    seteuid(getuid(this_object()));
    set_board_name(AC_EBOARDVAR);
    set_num_notes(30);
    set_silent(1);
    set_show_lvl(1);
    set_no_report(1);
    set_keep_discarded(0);
}
