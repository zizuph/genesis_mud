inherit "std/board.c";
#include "../defs.h"

create_board()
{
    seteuid(getuid(this_object()));
    set_name(({"scroll","board"}));
    set_short("ancient scroll");
    set_board_name(ROOM_DIR+"mboard/board");
    set_num_notes(60);
    set_anonymous(0);
    set_silent(1);
    set_show_lvl(0);
    set_remove_lvl(1);
    set_remove_str("You have to be a wizard to do that!\n");
}
