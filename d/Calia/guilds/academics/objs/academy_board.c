/* 
 * Academy of Elemental Arts Bulletin Board
 * 
 * This board will be present guild specific announcements and general
 * discussions by the Academics.
 *
 * Created by Petros, September 2009
 */

#pragma save_binary

#include <std.h>
#include <macros.h>
#include "defs.h"

inherit "/std/board";

public void
create_board()
{
    set_name("board");
    add_name( ({ "academy bulletin board", "bulletin board",
                 "academy board" }) );
    set_short("Academy bulletin board");
    set_board_name(ACADEMIC_BOARD_NOTES);
    set_num_notes(50);
    set_silent(0);
    set_show_lvl(0);
    set_remove_rank(WIZ_NORMAL);
    set_remove_str("You can't do that.\n");
}
