/**********************************************************************
 * - cboard.c                                                       - *
 * - Common board in SaMorgan                                       - *
 * - Created by Damaris@Genesis 12/2000                             - *
 **********************************************************************/

#pragma strict_types
#include "../defs.h"
#include <stdproperties.h> 
inherit "/d/Khalakhor/std/room";
public void load_board();

/*********************************************************************
 * - This adds the gks to the room so NPC's know where they are.   - *
 *********************************************************************/
public int *
query_local_coords()
{
	return ({6, 5});
}

public int *
query_global_coords()
{
	return SAMORGAN_COORDS;
}
void
create_khalakhor_room()
{
	set_short("Common Board Area");
	set_long("   This is a small cozy room, which contans the common "+
	"board. This board has been placed here by immortals. There "+
	"is a large notice in front of the board.\n");
	add_item(({"area", "room", "common room"}), query_long);
	add_item(({"south", "north", "east", "west", "southeast", "southwest", "northwest", "northeast"}),
	"There is a wall in that direction.\n");
	add_item(({"walls","wall"}),
	"There are lanterns fixed on the walls.\n");
	add_item(({"floor","ground"}),
	"The floor on which you are standing seems very firm, and is "+
	"made of darkened wood.\n");
	add_item(({"wood"}),
	"The wood is sturdy and dark. Perfect for flooring.\n");
	add_item(({"lantern","lanterns"}),
	"The lanterns are fixed firmly to the wall, and cannot be "+
	"taken.\n");
	add_item(("notice"),
	"The notice reads:\n" +
	"Only immortals can write on this board. It is to help in "+
	"the communication between immortals and mortals "+
	"concerning this realm.\n");
	
	add_prop(ROOM_I_INSIDE, 1);
	add_prop(ROOM_I_LIGHT, 1);
	add_exit("board", "out");
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
