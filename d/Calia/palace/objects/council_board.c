/* Calian Council board.

  History:  31.5.96    mudlib 1.0 updates                         Maniac 
            26.1.95    query_wiz_rank replaces query_wiz_level    Maniac
            16.1.96    check writer and remover too               Maniac
*/
     


#pragma save_binary

inherit "std/board.c";
#include "defs.h"
#include <std.h>
#include COUNCIL_HEADER


void
create_board()
{
    seteuid(getuid(THIS));
    set_name("board");
    set_short("the board of the Calian Council");
    set_board_name(TEXT("council_msgs"));
    set_num_notes(30);
    set_silent(0);
    set_show_lvl(0);
    set_remove_rank(WIZ_ARCH); /* real checks are done in allow_remove() */ 
    set_remove_str("You can't do that.\n"); 
}


int
council_board_check()
{
    object tp = TP;

    return (COUNCIL_CODE->is_council_member(capitalize(tp->query_real_name())) 
            || COUNCIL_CODE->is_calian_wiz(tp) || 
            (WIZ_CHECK >= WIZ_ARCH)); 
}


int
allow_remove()
{
     return council_board_check(); 
}


int 
block_reader()
{
     return !council_board_check(); 
}


int 
block_writer()
{
    return !council_board_check();
}

