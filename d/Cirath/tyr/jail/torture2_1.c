/*
* Created by: Luther
* Date: 11 August 2001
*
* File: /d/Cirath/tyr/jail/jail2_6.c
* Comments: Standard torture room in Tyr's Jail
*/

inherit "/std/room";
#include "defs.h"

void
create_room()
{
	add_prop(ROOM_I_INSIDE, 1);
	set_short("Torture room");
	set_long("The torture room looks deceiving, coming from the west you "
		+"had no idea what to expect. The room is lit by torches that "
		+"are fastened to the walls. In the middle of the room is a big "
		+"table and along side one wall stands a large rack. Against the "
		+"other wall you see chains hanging giving you a weird feeling "
		+"of being watched.\n");

	add_item("table", "The table is big, nearly 15 feet long, and "
		+"covering most of the room. Underneath the table you see cogwheels "
		+"on each end which are used to stretch the table. You can't help "
		+"but think of all the pain that table has caused to prisoners.\n");
	
	add_item("chains", "Upon closer examination you notice that the chains "
		+"are covered in blood. Making you think that they where used "
		+"for more then just holding a prisoner.\n");
		
	add_exit(TYR_JAIL + "jail2_7.c", "west", 0,1);
	reset_room();
}
