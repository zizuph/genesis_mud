inherit "/std/board";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_board()
{
   set_board_name(KALAD(log/merchants_private_board_data));
   set_num_notes(30);
   set_anonymous(0); /*no anonymous posts*/
   set_silent(0);    /*not silent */
   set_show_lvl(0);  /*no levels*/
   set_remove_lvl(10); /*only wizzes*/
   set_remove_str("Only wizards can do that.");
   set_keep_discarded(1); /*keep them for later reference*/
   set_err_log(KALAD(log/errors));
}
