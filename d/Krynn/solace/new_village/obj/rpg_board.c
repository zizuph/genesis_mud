#include <macros.h>

inherit "/std/board";

#define BOARD_ERROR "/d/Genesis/log/board_error"
#define RPG_BOARD   "/d/Genesis/rpg/rpg_board"

void
create_board()
{
   seteuid(getuid(TO));
   set_board_name(RPG_BOARD);
   set_num_notes(20);
   set_anonymous(0);
   set_silent(0);
   set_show_lvl(1);
   set_remove_lvl(15);
   set_remove_str("Only a wizard may remove these notes!\n");
   set_err_log(BOARD_ERROR);
   set_no_report(0);
   set_keep_discarded(0);
}
