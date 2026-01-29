/* 
 * /d/Kalad/common/guilds/khiraa/temple/obj/kboard.c
 * Purpose    : The board of the guild of the Khira
 * Located    : ~khiraa/temple/rooms/t5
 * Created By : Sarr 11.Mar.97
 * Modified By: 
 */ 

#pragma save_binary
#pragma strict_types
inherit "/std/board";
#include <std.h>
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h"
#include "/d/Kalad/defs.h"


void
create_board()
{
    set_board_name("/d/Kalad/common/guilds/khiraa/log/kboard_data");
    set_short("onyx board");
    set_long("This is board is made of pure onyx. Along the sides, "+
    "you see many platinum grim-looking skulls placed. The eyes "+
    "of the skull glow with an eerie green color.\n");
    set_num_notes(50);
    set_silent(0);
    set_show_lvl(1);
    set_remove_rank(WIZ_NORMAL);
    set_remove_str("You are not allowed to remove that note.\n");
}

int
block_reader()
{
    if(TP->query_real_name() == "decius")
        return 0;
    if(!IS_LP(TP) && !IS_DK(TP))
        return 1;
}

int
block_writer()
{
    if(TP->query_real_name() == "decius")
        return 0;
    if(!IS_LP(TP) && !IS_DK(TP))
        return 1;
}
