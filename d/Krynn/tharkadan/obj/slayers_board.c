/*
 * A board for the Doomseekers faction of the Neidar
 */

#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <std.h>

inherit "/std/board";

void
create_board()
{
    seteuid(getuid(TO));

    add_name(({"board"}));
    add_adj(({"hardwood","notice"}));
    set_short("hardwood notice board");
    set_long("This is a great hardwood notice board, used by dwarves " +
        "to post notices largely about grudges, mining, grog, or the " +
        "latest giant slain.\n");
    set_board_name(SLAYER_BOARD);
    set_num_notes(30);
    set_silent(0);
    set_show_lvl(0);
    set_no_report(0);
    set_keep_discarded(0);
}

public int
block_writer()
{
    if(TP->query_race_name() == "dwarf")
        return 0;

    if (SECURITY->query_wiz_level(TP->query_real_name()))
        return 0;

    write("This board is for dwarves. You cannot post here.\n");
    return 1;
}

public int
block_reader()
{
    return 0;
}

