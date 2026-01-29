
/* File name: archer_board.c
 * Elven Archers guild board.
 *
 * Blizzard, 8.11.2003
 */
 
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "../guild.h"

inherit  "/std/board";


void
create_board()
{
    seteuid(getuid(TO));
    set_short("small table");
    add_name("table");
    add_adj("small");
    set_long("This is a small table with a pile of papers lying on it. " +
        "The guild members leave notes here so others can read them later.\n");

    set_board_name(ARCHER_BOARD);
    set_num_notes(30);
    set_silent(0);
    set_show_lvl(1);
    set_no_report(0);
    
    set_keep_discarded(0);
}
