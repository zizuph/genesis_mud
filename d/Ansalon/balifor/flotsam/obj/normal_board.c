#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"

inherit "/std/board";

void
create_board()
{
   seteuid(getuid(TO));
   set_board_name(NORMAL_BOARD);
    set_num_notes(21);
   set_silent(0);
   set_show_lvl(1);
   set_no_report(0);
   set_keep_discarded(0);
}
