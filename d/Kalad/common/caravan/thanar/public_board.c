inherit "/std/board";
#include <std.h>
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_board()
{
    set_board_name(KALAD(log/than_pub));
    set_num_notes(30);
    set_silent(0);    /*not silent */
    set_show_lvl(0);  /*no levels*/
    set_remove_rank(WIZ_NORMAL);
    set_remove_str("Only wizards can do that.");
    set_keep_discarded(1); /*keep them for later reference*/
    /*
       set_err_log(KALAD(log/errors));
    */
}
