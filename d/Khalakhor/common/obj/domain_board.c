/*
 * khalakhor_domain_board.c
 *
 * Name says it all, wizard domain board for Khalakhor.
 *
 * Khail - March 25/97
 */
#pragma save_binary

inherit "/std/board.c";
#include "/d/Khalakhor/sys/defs.h"
#include <std.h>

public void
create_board()
{
    set_name("board");
    set_short("Khalakhor domain board");
    set_board_name("/d/Khalakhor/private/boards/domain_board");
    set_num_notes(80);
    set_show_lvl(0);
    set_remove_rank(WIZ_NORMAL);
    set_remove_str("You can't do that.\n"); 
}

/*
 * Function name: allow_remove
 * Description  : Restricts removal access to Khalakhor wizards
 *                and admin.
 * Arguments    : n/a
 * Returns      : 0 - Can't remove.
 *                1 - Can remove.
 */
public nomask int
allow_remove()
{
    /* Allow Khalakhor wizards to remove. */
    if (SECURITY->query_wiz_dom(TIQRN) == "Khalakhor")
	return 1;
    /* Allow arches + to remove. */
    if (SECURITY->query_wiz_rank(TIQRN) >= WIZ_ARCH)
	return 1;
    if (SECURITY->valid_write_all_sanction(TIQRN, "Khalakhor"))
	return 1;
    /* Disallow anyone else to remove. */
    return 0;
}

/*
 * Function name: block_writer
 * Description  : Prevents mortals from writing to this board.
 * Arguments    : n/a
 * Returns      : 0 - Player is allowed to write (a wiz).
 *                1 - Player is not allowed to write (a mortal).
 */
public nomask int
block_writer()
{
    return (SECURITY->query_wiz_rank(TIQRN) <= WIZ_MORTAL);
}

/*
 * Function name: block_reader
 * Description  : Prevents mortals from reading this board.
 * Arguments    : n/a
 * Returns      : 0 - Player is allowed to read (a wiz).
 *                1 - Player is not allowed to read (a mortal).
 */
public nomask int
block_reader()
{
    /* Allow Khalakhor wizards to read. */
    if (SECURITY->query_wiz_dom(TIQRN) == "Khalakhor")
	return 0;
    /* Allow arches to read. */
    if (SECURITY->query_wiz_rank(TIQRN) >= WIZ_ARCH)
	return 0;
    /* Deny everyone else */
    return 1;
    //    return (SECURITY->query_wiz_rank(TIQRN) <= WIZ_MORTAL);
}
