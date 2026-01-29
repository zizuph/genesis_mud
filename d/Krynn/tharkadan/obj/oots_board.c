/*
 * A board for the Holy Order of the Stars
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

    add_name(({"tree","fir tree"}));
    set_short("fir tree covered in notes");
    set_long("This is a fir tree with numerous notes nailed to it.\n");
    set_board_name(OOTS_BOARD);
    set_num_notes(30);
    set_silent(1);
    set_show_lvl(0);
    set_no_report(0);
    set_keep_discarded(0);
}

public int
block_writer()
{
    if(TP->query_guild_name_lay() == "Holy Order of the Stars")
        return 0;

    if (SECURITY->query_wiz_level(TP->query_real_name()))
        return 0;

    write("You are unable to post anything to the fir tree here.\n");
    return 1;
}

public int
block_reader()
{
    if(TP->query_guild_name_lay() == "Holy Order of the Stars")
        return 0;

    if (SECURITY->query_wiz_level(TP->query_real_name()))
        return 0;

    write("You can't make heads nor tails of what is written in these " +
        "notes for some reason!\n");
    return 1;
}

