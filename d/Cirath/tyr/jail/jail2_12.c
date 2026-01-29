/*
* Created by: Luther
* Date: 11 August 2001
*
* File: /d/Cirath/tyr/jail/jail2_12.c
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
		+"all the corners of the room. A table sits in the middle "
		+"of the room. The corridor is lit by torches that "
		+"are fastened to the walls.\n");

	add_item("cell", "There is a cell to the northeast. It looks very dark "
		+"in there or maybe its just your imagination.\n");

	add_item("corridor", "The corridor runs in every corner of the room. "
                +"It looks well used, guards patrol the corridor regulary.\n");

	add_item("table", "The table sits in the middle of the room. Upon "
		+"closer inspection you notice a small drawer in the table.\n");

	add_item("drawer", " The small drawer in the table is alittle hard to "
		+"see. you wonder what might be in it.\n");

	add_cmd_item("drawer", "open", "You try to open the dawer but find "
		+"it is locked.\n"); 

	add_cmd_item(({"torches", "torch"}), "pull", "A silent creak is "
		+"heard as you pull the torch, but you cannot pull it "
		+"loose.\n");

	add_exit(TYR_JAIL + "jail2_13.c", "northwest", 0,1);
	add_exit(TYR_JAIL + "cell2_4.c", "northeast", 0,1);
	add_exit(TYR_JAIL + "jail2_5.c", "southeast", 0,1);
	add_exit(TYR_JAIL + "jail2_7.c", "southwest", 0,1);
	reset_room();
}
