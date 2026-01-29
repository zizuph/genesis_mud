inherit "/std/board";
#include <std.h>
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_board()
{
   set_short("obsidian board");
   set_board_name(KALAD(log/than_priv));
   set_num_notes(50);
   set_silent(0);    /*not silent */
   set_show_lvl(1);  /*show levels*/
   set_remove_rank(WIZ_NORMAL);
   set_remove_str("Only wizards can do that.");
   set_keep_discarded(1); /*keep them for later reference*/
/*
   set_err_log(KALAD(log/errors));
*/
}
