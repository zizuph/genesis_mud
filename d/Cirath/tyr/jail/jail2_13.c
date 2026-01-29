/*
* Created by: Luther
* Date: 12 August 2001
*
* File: /d/Cirath/tyr/jail/jail2_13.c
* Comments: Standard corridor in Tyr's Jail
*/

inherit "/std/room";
#include "defs.h"
#include "/d/Cirath/common/teamer.h"

void
reset_room()
{
    bring_room_team(TYR_NPC+"jailgrd2.c", 1, 1);
}

void
create_room()
{
	add_prop(ROOM_I_INSIDE, 1);
	set_short("corridor");
	set_long("The corridor makes a ninety degree turn here, with two "
		+"prisoner cells intersecting it. There is a window in the "
		+"north wall.  The floor in the corridor is full of sand "
		+"and dust. The corridor is lit by torches that are fastened "
		+"to the walls.\n");

	add_item(({"cell", "cells"}), "There is a cell to the east and west of "
		+"here. They look very dark and unsettling. You think you "
		+"should leave them be, you never know when a prisoner might "
		+"try to escape this place.\n");

	add_item("corridor", "The corridor runs from the southwest to the "
                +"southeast. It looks well used, guards patrol the corridor "
                +"regulary.\n");
	
	add_item(({"floor", "sand", "dust"}), "Sand and dust is all over the "
	 	+"floor.\n");

	add_item("window", "Looking out the window you only see the sky. "
		+"Given the height it is above the floor, you think it "
		+"was meant for light during the daytime.\n");

	add_cmd_item(({"torches", "torch"}), "pull", "A silent creak is "
		+"heard as you pull the torch, but you cannot pull it "
		+"loose.\n");

	add_exit(TYR_JAIL + "cell2_2.c", "west", 0,1);
	add_exit(TYR_JAIL + "cell2_3.c", "east", 0,1);
	add_exit(TYR_JAIL + "jail2_12.c", "southeast", 0,1);
	add_exit(TYR_JAIL + "jail2_10.c", "southwest", 0,1);
	reset_room();
}
