
/* File name: warfare_board.c
 * Board where warfare reports are posted
 *
 */

#include <macros.h>
#include <std.h>
#include "/d/Krynn/common/defs.h"
#include "defs.h"

inherit  "/std/board";

void
create_board()
{
    seteuid(getuid(TO));
    set_short("notice board");
    add_adj("notice");
    set_long("This is a notice board where reports are posted " +
        "in relation to the final outcome of the War of the " +
        "Lance in Krynn.\n");

    set_board_name(LOG + "boards");
    set_num_notes(50);
    set_silent(0);
    set_show_lvl(1);
    set_no_report(0);

    set_keep_discarded(0);
}

public int
block_writer()
{

    if(TP->query_npc())
        return 0;

    if (SECURITY->query_wiz_level(TP->query_real_name()))
        return 0;

    write("The dark-bearded human in mercenary garb stops you " +
        "from posting on the notice board.\n");
    return 1;
}
