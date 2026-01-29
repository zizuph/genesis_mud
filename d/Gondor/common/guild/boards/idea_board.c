#pragma save_binary
#pragma strict_types

inherit "/std/board.c";

#include <std.h>

#include "/d/Gondor/defs.h"

void
create_board()
{
    set_board_name(BOARD_DIR + "ideaboard");
    set_num_notes(30);
    set_silent(0);
    set_show_lvl(1);
    set_remove_rank(WIZ_NORMAL);
    set_remove_str("Nope, you cannot remove that note.\n");
}

/*
 * Function name: block_reader
 * Description  : If this_player() is not allowed to read notes of other
 *                people on this board, this function should be used to
 *                block access. If you print an error message on failure,
 *                please check whether this_player() is in the environment
 *                of the board.
 * Returns      : int - true if the player is NOT allowed to read.
 */
public int 
block_reader()
{
    string name = TI->query_real_name();

    if ((SECURITY->query_wiz_rank(name) >= WIZ_ARCH) ||
	(member_array(SECURITY->query_wiz_dom(name),
	    ({ "Gondor", "Mordor", "Shire", "Rhovanion" }) ) >= 0))
    {
	return 0;
    }

    /* test for present added by Mrpr for use with his soul, Mercade */
    if (present(TI, environment(TO)))
	write("Only wizards of Middle Earth are allowed to handle this board.\n");
    return 1;
}

public int
block_writer()
{
    string name = TI->query_real_name();

    if ((SECURITY->query_wiz_rank(name) >= WIZ_ARCH) ||
	(SECURITY->query_wiz_dom(name) == "Gondor"))
    {
	return 0;
    }

    if (present(TI, environment(TO)))
	write("Only wizards of Gondor are allowed to handle this board.");
    return 1;
}

public int allow_remove() { return !block_writer(); }

