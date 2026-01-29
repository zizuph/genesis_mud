/* Notice board for mortals. ~mucalytic/shaangsei/hills/objects/notice_board */

inherit "/std/board";

#include "../defs.h"
#include "/sys/macros.h"
#include "/sys/language.h"

void create_board()
{
    set_adj("notice");
    add_name("notice_board");
    set_short("notice board");

    set_board_name(DATA + "notice_board");
    set_num_notes(20);
    set_silent(0);
}
