/*
* Created by: Chaos
* Date: 5 April 1995
*
* File: /d/Cirath/katakoro/encampment/yurts/yurt2.c
* Comments: Beadworker's Yurt	,edited by Luther Sept 2001
*/

#pragma save_binary

inherit "/std/room";
#include "defs.h"
#include "/d/Cirath/common/mobber.h"

void
reset_room()
{
   	bring_room_mob("beadworker",KAT_NPC+"beadworker.c",1,1);
}

void
create_room()
{   
    	set_short("Beadworker's yurt");
    	set_long("This yurt is home to a beadworker. All manner of beads and "+
		"carvings are scattered about the yurt in various stages of "+
		"completion. The yurt is also littered with the shavings that "+
		"result from the beadworkers craft.\n");

    	add_item(({"beads","carvings"}),"These beads and carvings are the work "+
		"of a master, unusual if one considers these people as "+
		"uncivilized barbarians. Each work is different, even two nearly "+
		"identical beads have an individual personality, as if it were "+
		"carved for a special purpose.\n");

    	INSIDE;

	add_exit(KAT_CAMP + "camp3","out", 0, 1);
    	reset_room();
}
