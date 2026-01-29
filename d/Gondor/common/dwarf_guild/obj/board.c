/*
 * /d/Gondor/common/dwarf_guild/obj/board.c
 *
 * This is the board in the dwarven race guild.
 *
 * /Mercade, 9 January 1994
 *
 * Revision history:
 * Eowul, Oktober 3rd 2008 - Board inherits gondor board
 */

#pragma save_binary

inherit "/d/Gondor/std/board";

#include <std.h>
#include "../dwarf.h"

void
create_board()
{
    set_board_name(DWARVEN_RACE_GUILD_BOARD);
    set_num_notes(20);
    set_silent(0);
    set_show_lvl(0);
    set_remove_rank(WIZ_LORD);
    set_remove_str(BSN("You are not allowed to remove that note."));
}
