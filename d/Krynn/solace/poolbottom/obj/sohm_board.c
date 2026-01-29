
/* File name: sohm_board.c
 * SoHM guild board
 *
 */

#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit  "/std/board";


void
create_board()
{
    seteuid(getuid(TO));
    set_short("notice board");
    add_adj("notice");
    set_long("This is the notice board within Poolbottom, school of High Magic, " +
      "where students can leave messages for fellow aspirants of Sorcery.\n");

    set_board_name(SOHM_BOARD);
    set_num_notes(50);
    set_silent(0);
    set_show_lvl(1);
    set_no_report(0);

    set_keep_discarded(0);
}
