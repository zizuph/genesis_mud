/*
 * /d/Genesis/mudlib/board.c
 *
 * This is the Sparkle lobby board in its temporary location.
 *
 * /Mercade, May 16 1996
 */

#pragma save_binary
#pragma strict_types

inherit "/std/board";

#include <std.h>

void
create_board()
{
    set_board_name("/d/Genesis/start/human/town/hub_save");
    set_num_notes(99);
    set_show_lvl(1);
    set_remove_rank(WIZ_LORD);
    set_remove_str("You are not allowed to remove that note.\n");
}
