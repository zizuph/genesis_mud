#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "../local.h"

inherit "/std/board";

void
create_board()
{
    seteuid(getuid(TO));
    set_short("notice board");
    set_long("The clan council board.\n");
    set_board_name(COUNCIL_BOARD);
    set_num_notes(20);
    set_silent(0);
    set_show_lvl(1);
    set_no_report(0);
    set_keep_discarded(0);
}
