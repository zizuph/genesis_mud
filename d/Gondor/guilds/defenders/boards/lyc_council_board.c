/* /d/Ravenloft/guilds/lycans/lair/boards/lyc_council_board.c
 *
 * Lycanthropes, guildboard.
 *
 * Nerull, 2015
 *
 */

#include <stdproperties.h>
#include <macros.h>
#include <std.h>
#include "defs.h";
#include "../guild.h";

inherit "/std/board";



public void
create_board()
{
    set_board_name(GUILD_DIR +"boards/lyc_council_board");
    set_num_notes(50);
    set_silent(1);
    set_show_lvl(0);
    set_remove_rank(WIZ_MORTAL);
    set_short("A black discussion board");
}



