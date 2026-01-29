#pragma strict_types
#pragma save_binary
 
inherit "/std/board";
#include "../museum.h"
void 
create_board()
{
    set_board_name(MUS+"mus_brd");
    set_num_notes(50);
    set_silent(1);
    set_show_lvl(0);
    set_keep_discarded(1);
    set_no_show_composite(1);
    set_remove_str("You are not permitted to do that.\n");
    set_name("board");
    add_name("paper");
    add_adj(({"poetry", "cork", "slip"}));
    set_long("It is a board made from cork. Upon it are "+
        "various notes, some legible, others faded with "+
        "age. In large letters, the words \"POEMS ONLY, "+
        "PLEASE -- OTHERS WILL BE REMOVED\" have been printed.\n");
}
