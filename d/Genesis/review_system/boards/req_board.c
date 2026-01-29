/*
 * The board used by the requests room.
 *                              Napture.
 */

inherit "/std/board";
#include <stdproperties.h>
#include "review.h"

create_board()
{
    set_board_name(PATH + "boards/rev_request_board");
    set_num_notes(30);
    set_anonymous(0);
    set_silent(1);
    set_show_lvl(0);
    set_remove_lvl(40);
    set_remove_str("Please leave these notes alone!\n");
    set_err_log(PATH + "boards/request_board_err");
    set_keep_discarded(1);
}        
