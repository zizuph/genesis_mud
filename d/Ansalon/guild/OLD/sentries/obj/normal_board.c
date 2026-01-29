#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit "/std/board";

void
create_board()
{
   seteuid(getuid(TO));
   set_board_name(KNIGHT_BOARD);
   set_num_notes(30);
   set_silent(0);
   set_show_lvl(1);
   set_no_report(0);
   set_keep_discarded(0);
}


