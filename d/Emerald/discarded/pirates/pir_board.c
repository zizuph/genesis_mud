inherit "std/board";

#include "defs.h"

create_board()

{
   set_short("The Pirates' bulletin board");
set_board_name(THIS_DIR+"pirate_board");
   set_num_notes(30);
    set_remove_rank(WIZ_LORD);
   set_remove_str("Sorry, only arch wizards can remove other peoples notes.\n");
   set_silent(0);
}
