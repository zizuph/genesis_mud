inherit "std/board.c";
#include "defs.h"

create_board(){
 seteuid(getuid(THIS));
 set_short("The Calian warrior's bulletin board");
 set_board_name(STAND_DIR+"bull_board");
 set_num_notes(30);
 set_anonymous(0);
 set_silent(0);
 set_show_lvl(0);
 set_remove_lvl(1);
 set_remove_str("Ya gotta be bigger in level to do that!\n");
}
