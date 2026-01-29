/*
* Created by: Luther
* Date: 10 August 2001
*
* File: /d/Cirath/tyr/jail/jail2_1.c
* Comments: Standard corridor in Tyr's Jail
*/

inherit "/std/room";
#include "defs.h"

void
create_room()
{
	add_prop(ROOM_I_INSIDE, 1);
	set_short("corridor");
	set_long("The corridor leads north to another room, judging from "
		+"the sound you think there are alot of people up here. "
		+"The corridor is lit by torches that are fastened to the "
		+"walls. In the corner you notice a staircase leading "
		+"down to the main floor.\n");		
	
	add_item(({"stairs", "staircase"}), "They are leading to the first floor. "
		+"There are drag marks on the stairs, and stains of some sort in "
		+"a red brownish colour. The steps are made of stone, and are "
                +"rather worn down.\n");

	 add_item("corridor", "The corridor to the north. It looks well used, "
	 	+"guards patrol the corridor regulary.\n");
		
	add_cmd_item(({"torches", "torch"}), "pull", "A silent creak is "
		+"heard as you pull the torch, but you cannot pull it "
		+"loose.\n");

	add_exit(TYR_JAIL + "jail1_1.c", "stairs", 0,1);
	add_exit(TYR_JAIL + "jail2_7.c", "north", 0,1);
	reset_room();
}
