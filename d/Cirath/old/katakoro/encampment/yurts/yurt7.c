/*
* Created by: Chaos
* Date: 19 April 1995
*
* File: /d/Cirath/katakoro/encampment/yurts/yurt7.c
* Comments: Clothworker's Yurt	,edited by Luther Oct. 2001
*/

#pragma save_binary

inherit "/std/room";
#include "defs.h"
#include "/d/Cirath/common/mobber.h"

void
reset_room()
{
   	bring_room_mob("clothworker",KAT_NPC+"clothworker.c",1,1);
}

void
create_room()
{
	set_short("Clothworker's yurt");
    	set_long("This yurt is home to a clothworker, or more specifically "+
		"a felt worker. Though, capable of working with other forms of "+
		"cloth, there is a great abundance of felt lying around ready "+
		"to be made into rugs for various uses. There are also some "+
		"unfinished kalats lying about, but it is obvious that those "+
		"are secondary to the felt.\n");

    	add_item(({"felt","rugs"}),"These felt rugs, when complete will be "+
		"used in the building of more yurts for various members of the "+
		"tribe. Some have been pounded with chalk to give them a "+
		"somewhat white look, others have been left in thier natural "+
		"state of black.\n");

    	INSIDE;

	add_exit(KAT_CAMP + "camp12","out", 0, 1);
    	reset_room();
}
