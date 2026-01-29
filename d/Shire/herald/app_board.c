/*
 * Herald application board
 *
 * Non heralds post on the board to let heralds know who want to join.
 * Only Heralds can read the board.
 * Finwe, January 2004
 */

#pragma save_binary
#pragma strict_types

inherit "/std/board.c";

#include <std.h>
#include "/d/Shire/sys/defs.h"
#include "/d/Shire/herald/herald.h"


void
create_board()
{
    set_long("This board has been placed here by the Heralds of the Valar. It " +
        "is sturdy and able to withstand the elements. Those wishing to " +
        "become a Herald of the Valar may post a note here to announce to " +
        "the guild their desire to join. Only other Heralds will be able " +
        "to read this board. Unsuitable notes are subject to removal.\n");
	set_board_name("/d/Shire/herald/board/applicants");
	set_num_notes(30);
	set_silent(1);
	set_show_lvl(0);
	set_remove_rank(WIZ_NORMAL);
    block_reader(); // only heralds may read the board.
	set_remove_str("Sorry, you cannot do that.\n");
	move(TO);

}


void
init()
{
    ::init();
}


int block_reader(int note) 
{ 
    return !IS_MEMBER(this_player());
}