#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "../local.h"

inherit "/std/board";

void
create_board()
{
    seteuid(getuid(TO));
    set_board_name(NORMAL_BOARD);
    set_num_notes(20);
    set_silent(1);
    set_show_lvl(1);
    set_no_report(0);
    set_keep_discarded(0);
}
