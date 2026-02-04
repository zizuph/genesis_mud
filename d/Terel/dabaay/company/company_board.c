inherit "/std/board.c";
#include <std.h>
#include "/d/Terel/include/Terel.h"

public void
create_board()
{
   seteuid(getuid(TO));
   set_short("Company Board");
   set_board_name(COMPANY + "board");
   set_num_notes(30);
   set_silent(0);
   set_show_lvl(0);
   set_remove_rank(WIZ_MAGE);
   set_remove_str("You have no such power.\n");
}

