/**
 * The Templar Knights' board
 * Louie 2004
 */
 
inherit "/std/board";

#include "../local.h"

void
create_board()
{
    seteuid(getuid(this_object()));
    
    set_short("notice board");
    set_long("This is the board used by the Templar Knights "+
        "of Takhisis.\n");
    set_num_notes(90);
    set_silent(0);
    set_board_name(TEMPLAR_BOARD);
    
        
}