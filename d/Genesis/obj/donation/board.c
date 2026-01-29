/*
 * /d/Genesis/obj/donation/board.c
 *
 * On this board, players can discuss the donations.
 *
 * Author: Mercade
 * Date  : August 18, 1998
 */
 
#pragma no_inherit
#pragma strict_types
 
inherit "/std/board";
 
#include <std.h>
 
/*
 * Function name: create_board
 * Description  : Constructor.
 */
void
create_board()
{
    set_short("bulletin board for discussing donation affairs");
    set_board_name("/d/Genesis/wiz/boards/donations");
    set_num_notes(50);
    set_silent(1);
    set_show_lvl(1);
    set_remove_rank(WIZ_LORD);
    set_remove_str("You are not allowed to remove that note.\n");
}
