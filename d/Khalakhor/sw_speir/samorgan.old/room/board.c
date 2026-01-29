/**********************************************************************
 * - board.c                                                        - *
 * - Messageboard in SaMorgan.                                      - *
 * - Created by Damaris@Genesis 12/2000                             - *
 **********************************************************************/

#pragma strict_types
#include "../defs.h"
#include <stdproperties.h>  
inherit "/d/Khalakhor/std/room";
#define BOARD_DIR (SMLOG + "board_data")

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
	object bb;
	set_short("SaMorgan's Message Center");
	set_long("   This is a fair sized room with a long wooden "+
	"table that has neatly stacked parchment papers with quills "+
	"and ink. The walls are sparse save for a couple of lanterns "+
	"and a large bulletin board that indicates the sole purpose of "+
	"this room. There is a small sign that indicates how to use the "+
	"board.\n");
	
	add_item(({"room", "message center", "area", "board room"}), query_long);
	add_item(({"south", "east"}),
	"That direction leads back out into the village street.\n");
	add_item(({"north", "west", "southeast", "southwest", "northwest", "northeast"}),
	"There is a wall in that direction.\n");
	add_item(({"papers", "parchment papers", "paper", "parchment paper"}),
	"The parchment papers are thin and neatly stacked on the wooden "+
	"table.\n");
	add_item(({"table", "wooden table"}),
	"The table is made from fine polished wood.\n");
	add_item(({"quill", "quills"}),
	"The quills are neatly placed next to the parchments.\n");
	add_item(({"ink", "inkwell", "black ink"}),
	"The inkwell is full of black ink.\n");
	add_item(({"walls","wall"}),
	"There are a couple of lit lanterns fixed on the walls along "+
	"with a bulletin board.\n");
	add_item(({"floor","ground"}),
	"The floor on which you are standing seems very solid, and is "+
	"made of darkened wood.\n");
	add_item(({"wood"}),
	"The wood is sturdy and dark.\n");
	add_item(({"lantern","lanterns"}),
	"The lanterns are lit and firmly attached to the walls, and "+
	"cannot be removed.\n");
	add_item(({"sign"}),
	"There is a sign that has been placed here. It "+
	"reads.\n"+
	"\t\t\t Instructions "+
	"\n\t'note <title>'             To post a note."+
	"\n\t'read <number>'            To read a note."+
	"\n\t'remove <number>'          To remove your note.\n");
	add_cmd_item("sign", "read", "\t\t\t Instructions "+
	"\n\t'note <title>'             To post a note."+
	"\n\t'read <number>'            To read a note."+
	"\n\t'remove <number>'          To remove your note.\n");
	
	add_prop(ROOM_I_INSIDE, 1);
	add_prop(ROOM_I_LIGHT, 1);
	
	add_exit("vil0604", "east");	
	add_exit("vil0703", "south");
	add_exit("cboard", "common");
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
