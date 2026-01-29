/*
* Created by: Chaos
* Date: 19 April 1995
*
* File: /d/Cirath/katakoro/encampment/yurts/yurt11.c
* Comments: Empress' Yurt	,edited by Luther Oct. 2001
*/

#pragma save_binary

inherit "/std/room";
#include "defs.h"
#include "/d/Cirath/common/mobber.h"

void
reset_room()
{
   	bring_room_mob("empress",KAT_NPC+"empress.c",1,1);
}

void
create_room()
{

    	set_short("the Empress' yurt");
    	set_long("This yurt is the home of the Khahan's wife, the empress. " +
		"The decore is spartan yet tasteful adding a livliness to the "+
		"usually dreariness of a yurt. The decor matched with the "+
		"abundance of light provided by the many lamps make this yurt "+
		"seem more hospitable than many of the others.\n");

	INSIDE;
	
	add_exit(KAT_CAMP + "camp12","out", 0, 1);
   	reset_room();
}


