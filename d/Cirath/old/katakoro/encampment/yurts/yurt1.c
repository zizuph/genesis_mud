/*
* Created by: Chaos
* Date: 5 April 1995
*
* File: /d/Cirath/katakoro/encampment/yurts/forge.c
* Comments: Sentry's Yurt	,edited by Luther Sept 2001
*/

#pragma save_binary

inherit "/std/room";
#include "defs.h"
#include "/d/Cirath/common/teamer.h"

void
reset_room()
{
    bring_room_team(KAT_NPC+"offguard.c", 1, 7);
}

void
create_room()
{      
    	set_short("Sentry's yurt");
    	set_long("This yurt acts as quarters for the arban of men assigned "+
		"as guards "+
		"to this part of the camp. It is kept in good order, with the "+
		"bedrolls of the men on duty placed out of the way. There is a "+
		"small cooking fire burning near the center. The only exit "+
		"is back out.\n");

    	add_item("yurt","This yurt has been kept very clean. The thick "+
		"felt carpet on the floor shows little sign of wear, and "+
		"there is no sign of dirt. The men have kept it so clean out "+
		"of fear of thier commanders.\n");
    	add_item("bedrolls","Currently these are occupied by four guards who "+
		"appear to be sleeping.\n");
    	add_item("fire","Something unusual smelling is cooking over the fire, "+
		"probably horsemeat, a common staple in a soldiers diet.\n");

    	INSIDE;

    	add_exit(KAT_CAMP + "camp2","out", 0, 1);
    	reset_room();
}
