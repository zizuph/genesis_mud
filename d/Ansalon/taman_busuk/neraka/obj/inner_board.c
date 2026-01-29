#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "../local.h"

inherit "/std/board";

void
create_board()
{
    seteuid(getuid(TO));
    set_board_name(INNER_BOARD);
    set_num_notes(30);
    set_silent(0);
    set_show_lvl(1);
    set_no_report(0);
    set_keep_discarded(0);
    set_long("This is the Neraka public forum.\n");
}

