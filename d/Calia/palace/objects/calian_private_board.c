
/* 
   The Calian private board.

   History:
            8/9/96   typo corrected                            Maniac
           31/5/96   mudlib 1.0 updates                        Maniac
           25/9/95   switch to inherit from board_lock.c       Maniac
           26.1.95   query_wiz_rank replaces query_wiz_level   Maniac
*/   

#pragma save_binary

inherit "/std/board";
#include "defs.h"
#include <std.h>
#include <macros.h>
#include COUNCIL_HEADER


void
create_board()
{
    seteuid(getuid(THIS));
    set_name("board");
    set_short("private bulletin board of the Calian guild");
    set_board_name(TEXT("calian_board_msgs"));
    set_num_notes(50);
    set_silent(0);
    set_show_lvl(0);
    set_remove_rank(WIZ_NORMAL);
    set_remove_str("You can't do that.\n");
}


/* Allow Calian Council to remove notes */ 
int
allow_remove()
{
    return (COUNCIL_CODE->is_council_member(TP->query_name()));  
}

