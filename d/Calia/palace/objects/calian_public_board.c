
/* Calian public board.

   History:
             31/5/96  mudlib 1.0 updates                         Maniac
             26.1.95  query_wiz_rank to replace query_wiz_level  Maniac
*/


#pragma save_binary

inherit "/std/board.c";
#include "defs.h"
#include <std.h>
#include COUNCIL_HEADER

void
create_board()
{
    set_name("board");
    set_short("public bulletin board of the Calian guild");
    set_board_name(TEXT("light_board_msgs"));
    set_num_notes(30);
    set_silent(0);
    set_show_lvl(0);
    set_remove_rank(WIZ_NORMAL);
    set_remove_str("You can't do that.\n"); 
}


/* Allow the Calian Council to remove notes */ 
int
allow_remove()
{
    return (COUNCIL_CODE->is_council_member(TP->query_name())); 
}

