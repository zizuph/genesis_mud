/* /d/Faerun/guilds/fire_knives/boards/contract_board.c
 *
 * Fire Knives, Contract board.
 *
 * Nerull, 2017
 *
 */

#include "/d/Faerun/defs.h"
#include "../guild.h";
#include <stdproperties.h>
#include <macros.h>
#include <std.h>

inherit "/std/board";

public void
create_board()
{
    set_board_name(FIREKNIVES_BOARDS_DIR + "guild_contracts");
    set_num_notes(50);
    set_silent(1);
    set_show_lvl(0);
    set_remove_rank(WIZ_MORTAL);
    set_short("wooden discussion board");
    set_long("This is a wooden discussion board. It is set firmly " 
        +"in the center of the room. Only fulfilled contracts and "
        +"their status are ment for this board.\n");
}
