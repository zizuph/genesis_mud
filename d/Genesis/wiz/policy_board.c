/*
 * /d/Genesis/wiz/policy_board.c
 *
 * This is the board on which the administration puts policy notes.
 *
 * /Mercade, 27 October 1994
 *
 * Revision history:
 */

#pragma save_binary

inherit "/std/board";

#include <std.h>
#include <macros.h>

void
create_board()
{
    set_board_name("/d/Genesis/wiz/boards/policy");
    set_num_notes(99);
    set_silent(0);
    set_show_lvl(0);
    set_remove_rank(WIZ_LORD + 1);
    set_remove_str("You are not allowed to remove that note. " +
	"Only archwizards and keepers are.\n");
}

int
block_writer()
{
    if (SECURITY->query_wiz_level(this_interactive()->query_real_name()) >
	WIZ_LORD)
    {
	return 0;
    }

    if (environment(this_player()) == environment(this_object()))
    {
	write("Only archwizards and keepers are allowed to make notes here.\n");
    }
    return 1;
}

int
allow_remove()
{
    if (SECURITY->query_wiz_level(this_interactive()->query_real_name()) >
	WIZ_LORD)
    {
	return 1;
    }

    if (environment(this_player()) == environment(this_object()))
    {
	write("Only archwizards and keepers are allowed to remove notes here.\n");
    }
    return 0;
}
