
/* 
    ~Calia/gelan/cadet/board.c 

    Board for the cadets of Gelan.

    Coded by Maniac@Genesis, March 1997 

    Copyright (C) Miguel Leith 1997
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
    set_short("private bulletin board of the " + GC_GUILD_NAME);
    set_board_name(GC_BOARD_NOTES);
    set_num_notes(50);
    set_silent(0);
    set_show_lvl(0);
    set_remove_rank(WIZ_NORMAL);
    set_remove_str("You can't do that.\n");
}
