/*
* Created by: Luther
* Date: 12 August 2001
*
* File: /d/Cirath/tyr/jail/jail2_9.c
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
		+"corridor intersecting it. There is a window in the west "
		+"wall. The corridor is lit by torches that are fastened "
		+"to the walls.\n");

	add_item(({"cell", "cells"}), "There is a cell to the north and south of "
		+"here. They look dangerous and inviting. You think you might be "
		+"thrown in one if you stay here any longer.\n");

	add_item("corridor", "The corridor runs from the northeast to the "
                +"southeast. It looks well used, guards patrol the corridor "
                +"regulary.\n");

	add_item("window", "Looking out the window you only see the sky. "
		+"Given the height it is above the floor, you think it "
		+"was meant for light during the daytime.\n");

	add_cmd_item(({"torches", "torch"}), "pull", "A silent creak is "
		+"heard as you pull the torch, but you cannot pull it "
		+"loose.\n");

	add_exit(TYR_JAIL + "cell2_5.c", "north", 0,1);
	add_exit(TYR_JAIL + "jail2_10.c", "northeast", 0,1);
	add_exit(TYR_JAIL + "jail2_2.c", "southeast", 0,1);
	add_exit(TYR_JAIL + "cell2_7.c", "south", 0,1);
	reset_room();
}
