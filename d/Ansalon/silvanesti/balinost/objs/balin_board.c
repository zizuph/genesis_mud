
#include <macros.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/silvanesti/balinost/local.h"


inherit "/std/board";

void
create_board()
{
    seteuid(getuid(TO));
    set_board_name(BALIN_BOARD);
    set_num_notes(25);
    set_silent(0);
    set_show_lvl(1);
    set_remove_str("You may not remove notes from this board!\n");
    set_no_report(0);
    set_keep_discarded(0);
    add_prop(MAGIC_I_RES_FIRE, 100);
    add_prop(OBJ_I_WEIGHT, 100000);
}
