#pragma save_binary

inherit "/std/board.c";
#include "/d/Terel/cedric/guild/guild_defs.h"
/*  
 *  This board is meant for players or wizards to submit songs or ideas for  
 *  the whole guild.
 *  Jorl 3/93
 *
 *  Changed to allow only the Guildmaster, his assistants, and the Cycle
 *  to write notes. This board is now reserved for important announcements
 *  from the administration.
 *  Cedric 9/94
 */


void
create_board()
{
	set_short("The Guildmaster's Board");
	
        set_board_name("/d/Terel/cedric/guild/Master_board");
}

#if 0
int check_writer()
{
    if (TP()->query_wiz_level() || TP()->query_special_title())
	return 0;
    else
    {
	TP()->CM("Sorry, this board is reserved for the Guildmaster, his "
		 + "assistants, and members of the Cycle.\n");
	return 1;
    }
}

int check_remove()
{
    if (TP()->query_wiz_level() || TP()->query_special_title())
	return 0;
    else
    {
	TP()->CM("Sorry, this board is reserved for the Guildmaster, his "
		 + "assistants, and members of the Cycle. Only they can "
		 + "remove notes from this board.\n");
	return 1;
    }
}
#endif
