/*
* Created by: Chaos
* Date: 19 April 1995
*
* File: /d/Cirath/katakoro/encampment/yurts/yurt5.c
* Comments: Kashik's Yurt	,edited by Luther Oct. 2001
*/

#pragma save_binary

inherit "/std/room";
#include "defs.h"
#include "/d/Cirath/common/teamer.h"

void
reset_room()
{
    	bring_room_team(KAT_NPC+"kashik.c", 1, 4);
}

void
create_room()
{
    	set_short("Kashik's yurt");
    	set_long("This yurt acts as quarters for the Kashik arban assigned "+
		"to guard this part of the Khahan's stockade. It is kept in "+
		"good order, with the "+
		"bedrolls of the men on duty placed out of the way. There is a "+
		"small cooking fire burning near the center, around which are "+
		"five guards, probably the ones that will go on duty next.\n");

    	add_item("yurt","This yurt has been kept very clean. The thick "+
		"felt carpet on the floor shows little sign of wear, and "+
		"there is no sign of dirt. The men have kept it so clean out "+
		"of fear of thier commanders.\n");
   	add_item("fire","Something unusual smelling is cooking over the fire, "+
		"probably horsemeat, a common staple in a soldiers diet.\n");

    	INSIDE;

	add_exit(KAT_CAMP + "camp8","out", 0, 1);
    	reset_room();
}
