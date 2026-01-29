/**********************************************************************
 * - board.c                                                        - *
 * - The Eil-Galaith board room                                     - *
 * - Created by Damaris@Genesis 09/Y2K                              - *
 * - Recoded by Damaris@Genesis 02/2002                             - *
 * - Recoded by Damaris@Genesis 04/2005                             - *
 * - Updates -                                                      - *
 * -           Increased board note capacity from 30 to 60          - *
 * -                                     - Damaris 04/2007          - *
 **********************************************************************/
#include "../guild.h"
#include <stdproperties.h>
inherit GUILD_ROOM;
#define BOARD_DIR "/d/Khalakhor/guilds/eilgalaith/log/board_data"

public void
create_guild_room()
{
	object bb;
	set_short("a simple room");
	set_long("   A simple room with a marble countertop placed "+
	"in the center. The walls are void of any decoration or "+
	"adornment. The only adornment are parchment papers stacked "+
	"neatly on the marble countertop, with quills placed next to "+
	"them. Just on the upper edge of the countertop an inkwell has "+
	"been placed that is quite full of ink.\n");
	add_item(({"room", "area"}), query_long);
	add_item(({"quill", "quills"}),
	"There are quills placed on a the marble countertop.\n");
	add_item(({"ink", "inkwell"}),
	"The inwell is sitting on the marble countertop and is quite "+
	"full of dark ink.\n");
	add_item(({"countertop", "marble countertop"}),
	"The marble countertop placed here is attatched firmly to the "+
	"center flooring with parchment papers, quills, and a full "+
	"inkwell have been placed on it.\n");
	add_item(({"parchment", "parchment papers", "papers", "paper"}),
	"The parchment papers have been stacked neatly on the marble "+
	"countertop for posting on the board.\n");
	
	add_prop(ROOM_I_INSIDE, 1);
	add_exit("start", "west");
	add_exit("c_board", "up");
	add_fail("auto", "A wall stops you.\n");
	
	setuid();
	seteuid(getuid());
	bb = clone_object("/std/board");
	bb->set_board_name(BOARD_DIR);
	bb->set_num_notes(60);
	bb->set_silent(0);
	bb->set_show_lvl(0);
	bb->move(this_object(), 1);
}
