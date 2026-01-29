/* /d/Faerun/guilds/fire_knives/boards/full_board.c
 *
 * Fire Knives, full member guildboard.
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
    set_board_name(FIREKNIVES_BOARDS_DIR + "guild_full");
    set_num_notes(50);
    set_silent(1);
    set_show_lvl(0);
    set_remove_rank(WIZ_MORTAL);
    set_short("iron discussion board");
    set_long("This is an iron discussion board. It is set firmly " 
        +"in the center of the room. Full members of the "
        +"may use this board to discuss tactics and various "
        +"other topics relevant for their day to day duty "
        +"and operations.\n");
}
