/* Mirandus - April 2020 - Updated at the request of the council
*  so they could remove the notes posted by Sehis that are spamming
*  their board.
*/

#pragma save_binary

#include "defs.h"
#include <std.h>
#include <macros.h>

inherit "/std/board.c";

void
create_board()
{
    setuid();
    seteuid(getuid());

    set_name("board");
    set_short("Elemental Clerics Discussion Board");
    set_board_name(ELEMENTALIST_DIR + "ec_board_notes");
    set_num_notes(50);
    set_silent(0);
    set_show_lvl(0);
    set_remove_rank(WIZ_NORMAL);
    set_remove_str("You have to be a wizard to do that!\n");
}

int
council_board_check()
{
    object tp = TP;
    return GUILD_MANAGER->query_is_ec_council(tp, 1);
}

varargs int allow_remove()
{
    return council_board_check();
}