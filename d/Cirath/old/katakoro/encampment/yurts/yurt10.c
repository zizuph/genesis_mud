/*
* Created by: Chaos
* Date: 5 April 1995
*
* File: /d/Cirath/katakoro/encampment/yurts/forge.c
* Comments: Empress' Guard's Yurt	,edited by Luther Sept 2001
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
    	set_short("Guard's yurt");
    	set_long("This yurt acts as quarters for the arban assigned "+
		"to guard the Empress. It is kept in good order, with the "+
		"bedrolls of the men on duty placed out of the way. There is a "+
		"small cooking fire burning near the center, around which "+
		"guards like to stand to warm up before there shifts begin.\n");

    	add_item("yurt","This yurt has been kept very clean. The thick "+
		"felt carpet on the floor shows little sign of wear, and "+
		"there is no sign of dirt. The men have kept it so clean out "+
		"of fear of thier commanders.\n");
    	add_item("fire","Something unusual smelling is cooking over the fire, "+
		"probably horsemeat, a common staple in a soldiers diet.\n");

    	INSIDE;
    
	add_exit(KAT_CAMP + "camp20","out", 0, 1);
    	reset_room();
}
