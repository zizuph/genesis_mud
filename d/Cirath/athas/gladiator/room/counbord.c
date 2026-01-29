/* counbord.c: The board of the council. */
#pragma save_binary
#pragma strict_types

inherit "/std/board";

#include "defs.h"
#include <std.h>

void
create_board()
{
    set_board_name(GLAD_LOG+"counboard");
    set_short("scratch covered table");
    add_name("table");
    set_adj("scratch");
    add_adj("covered");
    set_long("A solid hexagon of wood, marred by scratches, "+
        "serves as table. Countless messages are spread across it.\n");
    set_num_notes(99);
    set_silent(0);
    set_no_report(1);
    set_remove_str("Kalak has forbidden that.\n");
}

int block_reader() { return (POSITION(this_player()) == POS_NONE); }

int block_writer() { return (POSITION(this_player()) == POS_NONE); }

int allow_remove(int note) { return (POSITION(this_player()) == POS_WIZ); }
