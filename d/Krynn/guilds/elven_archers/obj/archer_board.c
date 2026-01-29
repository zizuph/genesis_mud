/**
 * This is the board for the archers guild
 */
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "../guild.h"

inherit  "/std/board";

void
create_board()
{
    seteuid(getuid(TO));
    set_short("pieces of parchments");
    set_name("parchments");
    add_name("parchment");
    add_name("messages");
    add_name("board");
    add_name("pieces of parchments");
    set_long("The tree trunk is filled with messages " +
             "shared between the archers.\n");
    set_board_name(BOARD);
    set_num_notes(50);
    set_silent(0);
    set_show_lvl(1);
    set_no_report(0);
    set_no_show_composite(1);
    set_keep_discarded(0);
}
