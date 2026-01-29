
/* 
   The board for discussions about the town of Gelan.

   Maniac 7/9/94

   Updated for mudlib 1.0, 30.5.96, Maniac
*/


inherit "/std/board.c";
#include "object.h"
#include <std.h>

void
create_board()
{
    set_name("board");
    set_short("public bulletin board of Gelan");
    set_board_name(GELAN_OBJECTS + "bull_board");
    set_num_notes(100);
    set_silent(0);
    set_show_lvl(0);
    set_remove_rank(WIZ_NORMAL);
    set_remove_str("You are not allowed to remove that note.\n");
}

