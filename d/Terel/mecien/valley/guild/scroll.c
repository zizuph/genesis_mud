/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
inherit "/std/board.c";
#include <std.h>

#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define TP   this_player()

public void
create_board()
{
    seteuid(getuid());
   set_name("scroll");
    add_name("board");
    add_name("scroll");
    set_short("Scroll of the Order");
    set_board_name("/d/Terel/mecien/valley/guild/board");
    set_num_notes(30);
    set_silent(0);
    set_show_lvl(0);
    set_remove_rank(WIZ_MAGE);
    set_remove_str("You have no such power.\n");
    set_no_report(1);
}

public int
block_reader()
{
    if (!MEMBER(TP)) return 1;
    return 0;
}

public int
block_writer()
{
    if (!MEMBER(TP)) return 1;
    return 0;
}

public int
allow_remove()
{
    if (MEMBER(TP) && TP->query_mystic_rank() >= MYSTIC_ARCHON)
        return 1;
    return 0;
}
