/*
* Created by: Luther
* Date: 11 August 2001
*
* File: /d/Cirath/tyr/jail/jail2_4.c
* Comments: Standard corridor in Tyr's Jail
*/
#pragma save_binary

inherit "/std/room";
#include "defs.h"
#include "/d/Cirath/common/teamer.h"

void
reset_room()
{
    bring_room_team(TYR_NPC+"jailgrd3.c", 1, 1);
}


void
create_room()
{
	add_prop(ROOM_I_INSIDE, 1);
	set_short("corridor");
	set_long("The corridor looks like a X shape, a corridor leading in "
		+"all the corners of the room. To the southeast is a cell, "
		+"you can hear chains rattling in there. The corridor is lit "
		+"by torches that are fastened to the walls.\n");

	add_item("cell", "There is a cell to the southeast. It looks very dark "
		+"in there and you start to shiver. You think you something evil "
		+"is in there, better not disturb it.\n");

	add_item("corridor", "The corridor runs in every corner of the room. "
                +"It looks well used, guards patrol the corridor regulary.\n");

	add_cmd_item(({"torches", "torch"}), "pull", "A silent creak is "
		+"heard as you pull the torch, but you cannot pull it "
		+"loose.\n");

	add_exit(TYR_JAIL + "jail2_7.c", "northwest", 0,1);
	add_exit(TYR_JAIL + "jail2_5.c", "northeast", 0,1);
	add_exit(TYR_JAIL + "cell2_12.c", "southeast", "@@se_block@@", 1);
	add_exit(TYR_JAIL + "jail2_3.c", "southwest", 0,1);
	reset_room();
}

int
se_block()
{
  object guard = present ("guard", TO);
  if(objectp(guard))
  {
 	if (!this_player()->query_wiz_level())
       	{
      	 TP->catch_msg(QCTNAME(guard)+" is standing right in the door, it is "
      		+"imposible to get by him.\n");
      	return 1;
    	}   
       	TP->catch_msg(QCTNAME(guard)+" lets you by.\n");
  }    
  return 0;
}
 