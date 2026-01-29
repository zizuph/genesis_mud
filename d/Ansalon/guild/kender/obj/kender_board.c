#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "../local.h"

inherit "/std/board";

void
create_board()
{
    seteuid(getuid(TO));
    add_name("branch");
    add_name("limb");
    add_adj("large");
    set_short("large branch with notes pinned all over it");
    set_long("This is a large branch with notes from " +
      "Kender of all walks of life pinned all over it. " +
      "No doubt most is meaningless " +
      "drivel, but you mind find some interesting scraps on it.\n");
    set_board_name(KEN_BOARD);
    set_num_notes(30);
    set_silent(0);
    set_show_lvl(1);
    set_no_report(0);
    set_keep_discarded(0);
}
