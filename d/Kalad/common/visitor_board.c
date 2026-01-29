inherit "/std/board";
#include <std.h>
#include "/d/Kalad/defs.h"

void
create_board()
{
    set_board_name("/d/Kalad/log/visitor_board_data");
    set_num_notes(30);
    set_silent(1);          /* silent */
    set_show_lvl(1);        /* show levels */
    set_remove_str("Only Lord's or higher may remove notes here!");
}
