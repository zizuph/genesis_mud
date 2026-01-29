/*
 *   Raumdor information board.
 *
 *   Nerull.   21/6.10
 */   
 
#pragma no_inherit
#pragma save_binary
#pragma strict_types

#include <macros.h>
#include <std.h>

inherit "/std/board";
#define BOARD_DIR "/d/Raumdor/log/rboard_data"

nomask void
create_board()
{
        set_name("board");
        add_name("bulletin board");
        set_short("old wooden bulletin board");
        set_long("This is an old wooden bulletin board with some notes " +
        "pinned on it. You don't know why it's erected here, but you " +
        "assume it's because to warn travellers from afar about the " +
        "places and dangers of the lands of Raumdor.\n");
        
        set_board_name(BOARD_DIR);
        set_num_notes(80);
        set_silent(1);
        set_show_lvl(1);
        set_remove_rank(WIZ_NORMAL);
        set_remove_str("You are not allowed to remove that note.\n");
        set_no_report(0);
        set_keep_discarded(1);
}



