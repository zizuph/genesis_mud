/* 
 * /d/Kalad/common/guilds/khiraa/temple/obj/kcboard.c
 * Purpose    : The circle board of the guild of the Khira
 * Located    : ~khiraa/temple/rooms/circle_private
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
    set_board_name("/d/Kalad/common/guilds/khiraa/log/kcboard_data");
    set_short("ethereal board");
    set_long("This board seems to be made out of mist, and floats "+
    "in the air with an eerie silence. Within it, the words of the "+
    "notes are displayed as red glowing characters.\n");

    set_num_notes(30);
    set_silent(0);
    set_show_lvl(1);
    set_remove_rank(WIZ_LORD);
    set_remove_str("You are not allowed to remove that note.\n");
}

int
block_reader()
{
    if(IS_GUILD_MASTER(TP))
        return 0;
    if(!IS_LP(TP) && !IS_DK(TP))
        return 1;
}

int
block_writer()
{
    if(!IS_LP(TP) && !IS_DK(TP))
        return 1;
}
