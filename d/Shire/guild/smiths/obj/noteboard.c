inherit "/d/Shire/std/board";

#pragma save_binary;

#include "/d/Shire/guild/smiths/smiths.h"
#include "/d/Shire/common/defs.h"
#include <std.h>

void
create_board() {
   set_board_name("/d/Shire/guild/smiths/board");
   set_num_notes(50);
   set_silent(0);
   set_show_lvl(0);
   set_remove_rank(WIZ_MORTAL);
   set_remove_str("Sorry, you can't do that\n");
//   set_err_log("/d/Shire/guild/smiths/log/board_err");
}

