/**********************************************************************
 * - cboard.c                                                       - *
 * - The Clan common board room                                     - *
 * - Created by Damaris 05/2006                                     - *
 **********************************************************************/
#pragma strict_types

#include "../guild.h"
#include <stdproperties.h>

inherit GUILD_ROOM;

#include "fireplace.c"

/* Prototype function */
public void load_board();

void
create_guild_room()
{
	set_short("a large landing");
	set_long("   This is a large landing that is used more or less "+
	"as a commons area for clans to come and mingle and get caught "+
	"up with the day-to-day business of the world. The walls are "+
	"pretty bare except for a large table with parchment papers "+
	"stacked neatly on top, with quills placed next to them. On "+
	"the upper edge of the table is an inkwell that is quite full "+
	"of ink. There also is a common board. Immortals as well as "+
	"mortals read this board. There is a large notice that is in "+
	"front of the board.\n");
	add_item(({"room", "area"}), query_long);
	
	add_cmd_item("notice", "read", "The notice reads:\n" +
	"Only immortals can write on this board.\nIt is to help in "+
	"the communication between immortals and mortals "+
	"concerning this realm.\n");
	
	add_cmd_item(({"board", "parchment", "countertop", "inkwell", "quills"}),(({"get","take","burn","climb"})),
	"You fail to do so and should be ashamed for even trying.\n");
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
	add_item(("notice"),
	"The notice reads:\n" +
	"Only immortals can write on this board.\nIt is to help in "+
	"the communication between immortals and mortals "+
	"concerning this realm.\n");
	
	add_item(({"quill", "quills"}),
	"There are quills placed on the table.\n");
	add_item(({"ink", "inkwell"}),
	"The inwell is sitting on the table and is quite full of "+
	"dark ink.\n");
	add_item(({"table", "tabletop"}),
	"The table is attached firmly to the wall and parchment "+
	"papers, quills, and an inkwell have been placed on it.\n");
	add_item(({"parchment", "parchment papers", "papers", "paper"}),
	"The parchment papers have been stacked neatly on the table "+
	"for posting on the board.\n");
	add_item(({"north", "east", "southeast", "northeast", "northwest"}),
	"There is a wall in that direction.\n");
	add_item(({"southwest"}),
	"An archway leading to sleeping area is in that direction.\n");
	add_item(({"south"}),
	"An archway leading to a meeting area is in that direction.\n");
	add_item(({"west"}),
	"An archway leading to a grand hall is in that direction.\n");
	
	add_exit("stairs", "down");
	add_exit("board", "south");
	add_exit("clan", "west");
	add_exit("start", "southwest");
	add_fail("auto", "A wall stops you.\n");
	
	load_board();
}

public void
load_board()
{
	object bb;
	seteuid(getuid(this_object()));
	bb = clone_object("/d/Genesis/obj/board");
	bb->move(this_object());
	return;
}

/**********************************************************************
 * - Give us some commands.                                         - *
 **********************************************************************/

public void
init()
{
	::init();
	init_fire();
}