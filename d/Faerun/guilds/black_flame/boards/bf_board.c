/* /d/Faerun/guilds/black_flame/boards/bf_board.c
 *
 * Black Flame guild board.
 *
 * Nerull, 2022
 *
 */

inherit "/std/board";

#include "/d/Faerun/defs.h"
#include "../guild.h";
#include <stdproperties.h>
#include <macros.h>
#include <std.h>

public void
create_board()
{
    set_board_name(BF_GUILD_DIR + "boards/bf_board_dir");
    set_num_notes(50);
    set_silent(1);
    set_show_lvl(0);
    set_remove_rank(WIZ_MORTAL);
    set_short("notice board");
    set_long("This is an orderly notice board hanging on the "
    +"west wall.\n");
}
