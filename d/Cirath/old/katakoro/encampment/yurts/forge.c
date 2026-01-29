/*
* Created by: Chaos
* Date: 5 April 1995
*
* File: /d/Cirath/katakoro/encampment/yurts/forge.c
* Comments: Forge Wagon	,edited by Luther Sept 2001
*/
 
#pragma save_binary

inherit "/std/room";
#include "defs.h"
#include "/d/Cirath/common/mobber.h"

void
reset_room()
{
   bring_room_mob("smith", KAT_NPC + "smith.c", 1, 1);
}

void
create_room()
{  
    	set_short("Forge Wagon");
    	set_long("This large wagon carries a huge forge, "+
		"possibly for when the Khahan's army is on the move. There are "+
		"several items lying about that would suggest that this forge "+
		"is under nearly constant use and even now a thin trail of smoke "+
		"lazily drifts upward from the coals. To the south is a yurt, "+
		"which could possibly be where the smith lives.\n");

	INSIDE;
	 
  	add_exit(KAT_YURTS + "yurt9", "south", 0, 1);  
  	add_exit(KAT_CAMP + "camp15", "out", 0, 1);
	reset_room();
}
