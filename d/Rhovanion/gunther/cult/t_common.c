inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/defs.h"
#include "guild.h"

object board;

create_room()
{
	set_short("Common board room.");
	set_long("This shadowy room seems to have no walls,"
		+" no floor, and no ceiling.  It is the room of the common board,"
		+" an insubstantial and mist-like creation, woven & drawn"
		+" from the fabric of time and space.  You sense that you may"
		+" somehow travel <back> to the gathering hall of the Cult of Melkor.\n");
	
	add_exit(CULT_DIR + "t_gather","back",0);
	
	add_prop(ROOM_I_LIGHT,1);
	add_prop(ROOM_I_INSIDE,1);
	
	load_board();
}
	
load_board()
{	
	object board;
	
	seteuid(getuid(TO));
	board = clone_object("/d/Genesis/obj/board");
	board->move(TO);
}

