inherit "/std/board.c";
#include <std.h>
#include "/d/Terel/include/Terel.h"

public void
create_board()
{
   seteuid(getuid(TO));
   set_short("Suggestions & Complaints Board");
   set_board_name(LAST_DIR + "board");
   set_num_notes(50);
   set_silent(0);
   set_show_lvl(0);
   set_remove_rank(WIZ_NORMAL);
   set_remove_str("You have no such power.\n");
}
