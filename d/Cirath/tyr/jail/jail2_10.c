/*
* Created by: Luther
* Date: 11 August 2001
*
* File: /d/Cirath/tyr/jail/jail2_10.c
* Comments: Standard corridor in Tyr's Jail
*/

inherit "/std/room";
#include "defs.h"
#include "/d/Cirath/common/mobber.h"

void
reset_room()
{ 	
    object npc = present ("guard", TO);
    if(!objectp(npc))
	{
    	    bring_room_mob("guard", TYR_NPC+"jailgrd2.c", 1, 1);
	}
}

void
create_room()
{
	add_prop(ROOM_I_INSIDE, 1);
	set_short("corridor");
	set_long("The corridor looks like a X shape, a corridor leading in "
		+"all the corners of the room. The corridor is lit by torches "
		+"that are fastened to the walls. There is a chair against "
		+"one wall and the floor is littered with garbage.\n");

	add_item("cell", "There is a cell to the northwest. It looks very dark "
		+"in there or maybe its just your imagination. You think you "
		+"heard something behind you, but when you look there is nothing "
		+"there.\n");

	add_item("corridor", "The corridor runs in every corner of the room. "
                +"It looks well used, guards patrol the corridor regulary.\n");

	add_item("chair", "The chair belongs to a guard, who sits is it "
		+"whenever he feels like it.\n");
	
	add_item(({"garbage", "floor"}), "The floor is littered with garbage, you "
		+"wonder why noone has cleaned it up.\n");	

	add_cmd_item(({"torches", "torch"}), "pull", "A silent creak is "
		+"heard as you pull the torch, but you cannot pull it "
		+"loose.\n");

	add_exit(TYR_JAIL + "cell2_1.c", "northwest", 0,1);
	add_exit(TYR_JAIL + "jail2_13.c", "northeast", 0,1);
	add_exit(TYR_JAIL + "jail2_7.c", "southeast", 0,1);
	add_exit(TYR_JAIL + "jail2_9.c", "southwest", 0,1);
	reset_room();
}
