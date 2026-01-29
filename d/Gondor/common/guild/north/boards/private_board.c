#pragma save_binary
#pragma strict_types

inherit "/std/board.c";
inherit "/d/Gondor/common/lib/binbit";

#include <std.h>

#include "/d/Gondor/defs.h"

void
create_board()
{
    set_board_name(RANGER_NORTH_DIR + "boards/private");
    set_num_notes(50);
    set_silent(0);
    set_show_lvl(0);
    set_remove_rank(WIZ_NORMAL);
    set_remove_str("Nope, you cannot remove that note.\n");
}

public int
allow_remove()
{
    if (query_bin_bits(1, 18, 2, this_player()) != 2)
        return 0;
    return 1;
}


