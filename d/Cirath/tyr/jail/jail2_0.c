/*
* Created by: Luther
* Date: 
*
* File: /d/Cirath/tyr/jail/
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
	set_long("The corridor makes a ninety degrees turn here, coming from "
		+"the southwest and turns to the southeast. A tapestry hangs "
		+"on the northern wall. The corridor is lit by torches that "
		+"is fastened to the walls.\n");

	add_item("tapestry", "The tapestry is big, nearly 15 feet wide, and "
		+"reaching from the floor all the way up to the ceiling. "
		+"The tapestry pictures a great battle in the artasian "
		+"desert.\n");

	add_cmd_item("tapestry", "pull", "You pull the tapestry but it is so "
		+"big that you can't pull it loose from the wall.\n"); 

	add_cmd_item(({"torches", "torch"}), "pull", "A silent creak is "
		+"heard as you pull the torch, but you cannot pull it "
		+"loose.\n");

	add_exit(TYR_JAIL + "corner1.c", "west", 0,1);
	add_exit(TYR_JAIL + "corner2.c", "east", 0,1);
	add_exit(TYR_JAIL + "jail1_5.c", "southeast", 0,1);
	add_exit(TYR_JAIL + "jail1_4.c", "southwest", 0,1);
	reset_room();
}
