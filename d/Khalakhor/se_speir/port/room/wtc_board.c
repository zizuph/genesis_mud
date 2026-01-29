inherit "/std/board.c";
#include <std.h>
#include "/d/Khalakhor/sys/defs.h"

public void
create_board()
{
   seteuid(getuid(TO));
   set_short("fence");
   set_board_name("/d/Khalakhor/se_speir/port/room/wtc_board");
   set_num_notes(50);
   set_silent(0);
   set_no_show();
   set_show_lvl(10);
   set_remove_rank(WIZ_NORMAL);
   set_remove_str("It would be rude to remove this note.\n");

}
