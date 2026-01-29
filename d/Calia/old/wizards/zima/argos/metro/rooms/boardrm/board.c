
/* Board for metro Argos */ 

inherit "/std/board.c";
#include "defs.h"
#include <std.h>

void
create_board()
{
    seteuid(getuid(THIS));
    set_name("board");
    set_short("Board of Argos");
    set_board_name(ROOM_DIR+"boardrm/board");
    set_num_notes(30);
    set_silent(0);
    set_show_lvl(0);
    set_remove_rank(WIZ_NORMAL);
    set_remove_str("You have to be a wizard to do that!\n");
}

