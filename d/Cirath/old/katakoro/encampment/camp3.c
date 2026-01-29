/*
* Created by: 
* Date: 
*
* File: /d/Cirath/katakoro/encampment/camp3.c
* Comments: edited by Luther Sept 2001
*/

inherit "/std/room.c";
#include "defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Cirath/common/mobber.h"

void
reset_room()
{
     bring_room_mob("kid",KAT_NPC + "kids.c",2,1);
}

void
create_room()
{
   	set_short("Barbarian camp");
   	set_long("Moving deeper into the encampment, the frequency of yurts "+
		"increases. All around people are going about their business, "+
		"some tending to the drying meats, others caring for their "+
		"horses and a few warrior are working with their weapons. To "+
		"the northwest is a particularly busy yurt, there is a peculiar "+
		"string hanging from the doorway, that may explain it's purpose.\n");

   	add_item("yurt","This yurt is similar to the many others that are in "+
		"the area, being made of thick felt rugs. However, this one "+
		"has a dull white tone about it from chalk that was pounded in, "+
		"when the yurt was made.\n");
   	add_item("doorway","Hanging over the doorway into the yurt is a long "+
		"string of intricately designed beads. Each one looks to have "+
		"been individually carved with great care. It is possible that "+
		"a beadworker lives and works in this yurt.\n");

   	add_exit(KAT_CAMP + "camp2","south", 0, 1);  
   	add_exit(KAT_CAMP + "camp4","north", 0, 1);  
  	add_exit(KAT_YURTS + "yurt2","enter", 0, 1, 1);  
   	reset_room();
}

