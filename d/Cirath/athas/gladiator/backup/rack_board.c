/**********************************************************************
 * - rack_board                                                     - *
 * - A special board for High Overseer to post on concerning racks. - *
 * - Created by Damaris@Genesis 09/2005                             - *
 **********************************************************************/

#pragma no_inherit
#pragma save_binary
#pragma strict_types

inherit "/std/board";

#include <macros.h>
#include <std.h>
#include "../guild.h"
#include "defs.h"
#define BOARD_DIR "/d/Cirath/athas/gladiator/log/overseer_data"

nomask void
create_board()
{
	remove_name(query_name());
	remove_pname(query_pname());
	add_name(OB_NAME(this_object()), 1);
	set_name("sign");
	set_short("special sign");
	set_long("A special sign that the High Overseer places important "+
	"information for Gladiators concerning the racks here.\n");
	set_no_show_composite(1);
        set_board_name(BOARD_DIR);
	set_num_notes(100);
	set_silent(0);
	set_show_lvl(1);
//	set_remove_rank(WIZ_LORD);
	set_remove_str("Sorry, only the High Overseer may remove.\n");
	set_no_report(0);
	set_keep_discarded(1);
}

nomask int
query_prevent_shadow()
{
	return 1;
}

nomask int
block_writer()
{
    if((MANAGER)->query_overseer(this_player()) == POS_HIGH || this_player()->query_wiz_level())
        return 0;

    return 1;
}

nomask int
block_discard(string file)
{
    if((MANAGER)->query_overseer(this_player()) == POS_HIGH || this_player()->query_wiz_level())
        return 0;

    return 1;
}

/* replacement of that 'gnome securing' message */

nomask void
reset_board()
{
	if (!random(5))
	{
		tell_room(environment(),
		"A small gnome appears and makes sure all notes are "+
		"securely placed in the " + short() + ".\nThe gnome "+
		"then leaves again.\n");
	}
}
