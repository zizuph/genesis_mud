/*
* Created by: Luther
* Date: 10 August 2001
*
* File: /d/Cirath/tyr/jail/jail2_7.c
* Comments: Standard corridor in Tyr's Jail
*/

inherit "/std/room";
#include "defs.h"

void
create_room()
{
	add_prop(ROOM_I_INSIDE, 1);
	set_short("corridor");
	set_long("This is the center corridor leading to all the cells. You hear "
		+"noise coming from all around you and the occasional scream can be "
		+"heard as well. Judging from the activity you think alot of people "
		+"were arrested today. The corridor is lit by torches and you "
		+"notice a chart on the wall.\n");
	
	add_item("corridor", "The corridor runs in all directions. It looks well "
		+"used, guards patrol the corridor regulary.\n");	
	
	add_item("chart", "You see alot of scratches and lines not being "
		+"able to make anything out.\n");

  	add_cmd_item("chart","read","Surely you jest, "+
    		"reading is illegal in Tyr!  Fortunately, the chart is "+
    		"examinable.\n");
	
	add_cmd_item(({"torches", "torch"}), "pull", "A silent creak is "
		+"heard as you pull the torch, but you cannot pull it "
		+"loose.\n");

	add_exit(TYR_JAIL + "office2_1.c", "west", 0,1);
	add_exit(TYR_JAIL + "torture2_1.c", "east", 0,1);
	add_exit(TYR_JAIL + "jail2_4.c", "southeast", 0,1);
	add_exit(TYR_JAIL + "jail2_2.c", "southwest", 0,1);
	add_exit(TYR_JAIL + "torture2_2.c", "north", 0,1);
	add_exit(TYR_JAIL + "jail2_1.c", "south", 0,1);
	add_exit(TYR_JAIL + "jail2_12.c", "northeast", 0,1);
	add_exit(TYR_JAIL + "jail2_10.c", "northwest", 0,1);
	reset_room();
}
