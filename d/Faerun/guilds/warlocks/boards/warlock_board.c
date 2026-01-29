/* /d/Faerun/guilds/warlocks/boards/warlock_board.c
 *
 * Warlocks, guildboard.
 *
 * Nerull, 2017
 *
 */

#include "/d/Faerun/defs.h"
#include "defs.h";
#include "../guild.h";
#include <stdproperties.h>
#include <macros.h>
#include <std.h>

inherit "/std/board";

public void
create_board()
{
    set_board_name(WARLOCK_BOARDS_DIR + "guild");
    set_num_notes(50);
    set_silent(1);
    set_show_lvl(0);
    set_remove_rank(WIZ_MORTAL);
    set_short("private board");
    set_long("This is a wooden discussion board. It is set firmly " +
        "in the center of the room. It is where Warlocks and Witches can " +
        "post notes of their travels, and anything else they deem necessary " +
        "for others to know of.\n");
}
