/* /d/Faerun/guilds/fire_knives/boards/applic_board.c
 *
 * Fire Knives, application guildboard.
 *
 * Nerull, 2019
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
    set_board_name(FIREKNIVES_BOARDS_DIR + "guild_applic");
    set_num_notes(50);
    set_silent(1);
    set_show_lvl(0);
    set_remove_rank(WIZ_MORTAL);
    set_remove_str("You are not permitted.\n");
    set_no_show_composite(1);
    set_short("wooden application board");
    set_long("This is a wooden application board. It is set firmly " 
        +"in the center of the room. Individuals who wish to "
        +"join the Brotherhood of the Fire Knives must "
        +"to post their formal application on this board.\n");
}


public int
block_reader(void)
{
    if (FIREKNIVES_MAPPINGS->query_assassin_rank(this_player()->query_name()) <= MAX_PROSPECT_RANK)
    {
        if (environment(this_player()) == environment(this_object()))
            write("You are permitted to view only your own posts on this board.\n");
        
        return 1;
    }

    return 0;
}


/*public int
block_writer(void)
{
    return block_reader();
}*/


public int
allow_remove(void)
{ 
    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(this_player()->query_name()) == 1 ||
        FIREKNIVES_MASTER->is_occ_mentor_fireknife(this_player()->query_name()) == 1 ||
        FIREKNIVES_MASTER->is_occ_thefist_fireknife(this_player()->query_name()) == 1)
    {
        if (present(this_player(), environment(this_object()))) 
            write("Since you are a member of the council, you may remove the note.\n");
        return 1; 
    }

    return 0;
}
