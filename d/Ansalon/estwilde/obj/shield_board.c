
/* File name: shield_board.c
 * Shieldbearers guild board in Iron Delving
 *
 * Blizzard, 4.12.2003
 */
 
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "../local.h"

inherit  "/std/board";


void
create_board()
{
    seteuid(getuid(TO));
    set_short("notice board");
    add_adj("notice");
    set_long("The board used by Shieldbearers to communicate with the " +
        "Clan members.\n");

    set_board_name(SHIELDBEARERS_BOARD);
    set_num_notes(20);
    set_silent(0);
    set_show_lvl(1);
    set_no_report(0);
    
    set_keep_discarded(0);
}
