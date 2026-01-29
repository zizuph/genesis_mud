#pragma save_binary
#pragma strict_types

inherit "/std/board";
#include <std.h>
#include "/d/Kalad/common/guilds/shadow_walkers/default.h"
#include "/d/Kalad/defs.h"


void
create_board()
{
    set_board_name("/d/Kalad/log/shadow_walkers_board_data");
    set_short("cracked wooden board");
    set_long("This is a dark, wooden board that has many "+
    "cracks in it. On it, you see a number of messages tacked "+
    "onto it with needles and daggers.\n");
    set_num_notes(50);
    set_silent(0);
    set_show_lvl(1);
    set_remove_rank(WIZ_NORMAL);
    set_remove_str("You are not allowed to remove that note.\n");
}

int
block_reader()
{
    if(TP->query_guild_name_lay() != GUILD_NAME)
        return 1;
}

int
block_writer()
{
    if(TP->query_guild_name_lay() != GUILD_NAME)
        return 1;
}
