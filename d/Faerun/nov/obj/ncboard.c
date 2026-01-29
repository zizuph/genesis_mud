#pragma save_binary
#pragma strict_types

inherit "/std/board";
#include <std.h>
#include <macros.h>
#include "../nov.h";
    
void
create_board()
{
    set_board_name(NOV_DIR +"obj/ncboard");
    set_num_notes(50);
    set_silent(1);
    set_show_lvl(0);
    set_remove_rank(WIZ_MORTAL);
    set_short("runed council board");
}
