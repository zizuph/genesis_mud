
inherit "/std/board.c";
#include "/d/Roke/common/defs.h"


object board;

 
create_board()
{
   check_reader();
   check_remove();

   board->set_board_name(ATUAN+"cape/guild/council");
        board->set_num_notes(30);
        board->set_anonymous(0);
        board->set_silent(1);
        board->set_show_lvl(1);
        board->set_remove_lvl(17);
        board->set_remove_str(
"Sorry but that is for high-level wizards only !\n");
        board->set_err_log(ATUAN + "board/board_err");
        board->move(TO);
}
 
