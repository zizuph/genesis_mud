/* File name: angler_board.c
 * Board for angler club
 */

#include <macros.h>
#include <std.h>
#include "/d/Krynn/common/defs.h"
#include "fishing.h"

inherit  "/std/board";

void
create_board()
{
    seteuid(getuid(TO));
    set_short("notice board");
    add_adj("notice");
    set_long("This is the notice board within the Lodge " +
        "of Distinguished Hunters and Anglers, where members " +
        "and visitors share news and stories.\n");

    set_board_name(FISH_LOG + "boards");
    set_num_notes(50);
    set_silent(0);
    set_show_lvl(1);
    set_no_report(0);

    set_keep_discarded(0);
}

public int
block_writer()
{
    return 0;
}
