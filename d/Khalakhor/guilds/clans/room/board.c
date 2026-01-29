/**********************************************************************
 * - board.c                                                        - *
 * - The Clan board room                                            - *
 * - Created by Damaris 05/2006                                     - *
 **********************************************************************/
#include "../guild.h"
#include <stdproperties.h>

inherit GUILD_ROOM;

#include "seated.c"
#include "fireplace.c"

#define BOARD_DIR "/d/Khalakhor/guilds/clans/log/board_data"

public void
create_guild_room()
{
	object bb;
	set_short("A meeting room");
	set_long("   This is a meeting room that is used more than "+
	"just day-to-day business of the world. It is for clans "+
	"together to discuss what is going on not just out in the "+
	"world but the happenings within the clans. The walls are "+
	"pretty bare except for a bulletin board and a large "+
	"fireplace. ");
	add_item(({"chair","chairs", "rug"}), seat_desc);
	add_my_desc(seat_desc, this_object());	
	add_item(({"entrance", "hall","room", "area"}), query_long);
	
	add_item(({"room", "area"}), query_long);
	add_item(({"fireplace"}),
	"The fireplace is quite large with a holder placed on one side "+
	"with tools to stoke the fire and logs on the otherside to "+
	"place on the fire.\n");
	add_item(({"tool", "tools", "poker", "fireplace poker"}),
	"There are tools in a holder next to the fireplace so one can "+
	"stoke the fire.\n");
	add_item(({"log", "logs", "stack"}),
	"Logs for the fire are piled in a neat stack next to the "+
	"fireplace.\n");
	add_item(({"north"}),
	"An archway leads to the commons area.\n");
	add_item(({"west"}),
	"An archway leads to the sleeping area in that direction.\n");
	add_item(({"northeast", "northwest", "southeast", "southwest", "south", "east"}),
	"There is a wall in that direction.\n");
	
	add_prop(ROOM_I_INSIDE, 1);
	add_prop(ROOM_I_LIGHT, 1);
	add_exit("start", "west");
	add_exit("cboard", "north");
	add_fail("auto", "A wall stops you.\n");
	
	setuid();
	seteuid(getuid());
	bb = clone_object("/std/board");
	bb->set_board_name(BOARD_DIR);
	bb->set_num_notes(30);
	bb->set_silent(0);
	bb->set_show_lvl(0);
	bb->move(this_object(), 1);
}
/**********************************************************************
 * - Give us some commands.                                         - *
 **********************************************************************/

public void
init()
{
	::init();
	init_seat();
	init_fire();
}
