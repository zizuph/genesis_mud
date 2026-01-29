inherit "std/board";

#pragma save_binary;

#include "/d/Shire/smiths/smiths.h"
#include "/d/Shire/common/defs.h"
#include <std.h>

void
create_board() {
   set_board_name("/d/Shire/smiths/board");
   set_num_notes(50);
   set_silent(0);
   set_show_lvl(0);
   set_remove_rank(WIZ_MORTAL);
   set_remove_str("Sorry, you can't do that\n");
//   set_err_log("/d/Shire/smiths/log/board_err");
}

init() {
   ::init();

   add_action ("remove", "remove");
}

int
remove(string str) {
   if ((TP->query_skill(SM_MASTER)!=1) || (!IS_MEMBER(TP)) ||
      (TP->query_wiz_rank(WIZ_NORMAL))) {
      write("You can't do that.\n");
      return 1;
   }
   remove_msg(str);
   return 1;
}

