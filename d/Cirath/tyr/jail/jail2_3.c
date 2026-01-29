/*
* Created by: Luther
* Date: 12 August 2001
*
* File: /d/Cirath/tyr/jail/jail2_3.c
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
	set_long("The corridor makes a ninety degree turn here, with a  "
		+"corridor intersecting it. There is a window in the south "
		+"wall. To the west and east you see cells.  The corridor "
		+"is lit by torches that are fastened to the walls.\n");

	add_item(({"cell", "cells"}), "There is a cell to the east and west of "
		+"here. They look dark and disturbing. You prefer to never "
		+"be put in one.\n");

	add_item("corridor", "The corridor runs from the northwest to the "
                +"northeast. It looks well used, guards patrol the corridor "
                +"regulary.\n");

	add_item("window", "Looking out the window you only see the sky. "
		+"Given the height it is above the floor, you think it "
		+"was meant for light during the daytime.\n");

	add_cmd_item(({"torches", "torch"}), "pull", "A silent creak is "
		+"heard as you pull the torch, but you cannot pull it "
		+"loose.\n");

	add_exit(TYR_JAIL + "cell2_10.c", "west", 0,1);
	add_exit(TYR_JAIL + "cell2_11.c", "east", 0,1);
	add_exit(TYR_JAIL + "jail2_2.c", "northwest", 0,1);
	add_exit(TYR_JAIL + "jail2_4.c", "northeast", 0,1);
	reset_room();
}
