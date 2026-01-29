/*
 * A board for the Mariner craft guild
 */

#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "guild.h"
#include <std.h>

inherit "/std/board";

void
create_board()
{
    seteuid(getuid(TO));

    add_name(({"board"}));
    add_adj(({"hardwood","notice"}));
    set_short("hardwood notice board");
    set_long("This is a great hardwood notice board, used by sailors " +
        "of the Guild of Mariners to share their tall tales.\n");
    set_board_name(MARINER_BOARD);
    set_num_notes(30);
    set_silent(0);
    set_show_lvl(0);
    set_no_report(0);
    set_keep_discarded(0);
}

public int
block_writer()
{
    if (SECURITY->query_wiz_level(TP->query_real_name()))
        return 0;

    if(!TP->query_guild_member(GUILD_NAME))
    {
        write("This board is for mariners. You cannot post here.\n");
        return 1;
    }

    return 0;
}

public int
block_reader()
{
    return 0;
}

