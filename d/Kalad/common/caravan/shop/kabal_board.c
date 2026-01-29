#include "../default.h"

inherit "/std/board";

#include <std.h>

create_board()
{
    set_board_name("/d/Kalad/log/kabal_board_data");
    set_num_notes(30);
    set_silent(0);
    set_show_lvl(0);
    set_remove_rank(WIZ_NORMAL);
    set_remove_str("Only wizzes can do that");
    set_keep_discarded(1);
}
