
/* 
   The Calian Trainees' board.

   History:
           15/4/02   modified from private board code          Maniac
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
    set_short("bulletin board for trainees of the Calian guild");
    set_board_name(CRPALACE_TEXTS + "trainee_board_msgs");
    set_num_notes(30);
    set_silent(0);
    set_show_lvl(0);
    set_remove_rank(WIZ_NORMAL);
    set_remove_str("You can't do that.\n");
}


/* Allow Calian Council to remove notes */ 
int
allow_remove()
{
    return (COUNCIL_CODE->is_council_member(capitalize(TP->query_real_name()))); 
}
