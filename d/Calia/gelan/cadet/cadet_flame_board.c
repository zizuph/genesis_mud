
/* 
    ~Calia/gelan/cadet/cadet_flame_board.c 

    Flame board for the cadets of Gelan.

    Coded by Maniac@Genesis, 19/4/99
*/   

#pragma save_binary

inherit "/std/board";
#include "cadet.h"
#include <std.h>
#include <macros.h>

void
create_board()
{
    set_name("board");
    set_short("flame board of the " + GC_GUILD_NAME);
    set_board_name(GC_DIR + "flame_notes/");
    set_num_notes(30);
    set_silent(0);
    set_show_lvl(0);
    set_remove_rank(WIZ_NORMAL);
    set_remove_str("You can't do that.\n");
}

