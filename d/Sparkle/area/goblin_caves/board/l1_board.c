/*
 * Board room
 * Boreaulam, August 2012
 */
#pragma strict_types
#include "defs.h"

inherit "/std/board";

public void        create_board();

/*
 * Function name:        create_board
 * Description  :        set up the board
 */
public void
create_board()
{
    set_board_name(GOBLIN_CAVES_DIR + "board/board_notes/");
    set_num_notes(50);
    set_silent(0);
    set_show_lvl(0);
    set_keep_discarded(1);
} /* create_board */
