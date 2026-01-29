/*
* Created by: 
* Date: 
*
* File: /d/Cirath/katakoro/encampment/camp15.c
* Comments: edited by Luther Sept 2001
*/


inherit "/std/room.c";
#include "defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Cirath/common/mobber.h"

void
create_room()
{
   	set_short("Barbarian camp");
   	set_long("This area is surrounded by yurts of various shapes and "+
		"sizes. For the most part these are homes to the members of "+
		"the Khahan's tribe. To the west is the residence of an "+
		"obvious outsider. It is a large wagon with a yurt attached "+
		"to it. There is a sign hanging from the wagon suggests that "+
		"this is the residence of a smith.\n");
	
   	add_item("wagon","This large wagon looks like it carries a forge, "+
		"possibly for when the Khahan's army is on the move. Thin "+
		"trails of smoke drift up from the forge now, suggesting "+
		"that it is constantly in use.\n");

  	add_exit(KAT_CAMP + "camp16","south", 0, 1);  
   	add_exit(KAT_YURTS + "forge","enter", 0, 1, 1);
  	add_exit(KAT_CAMP + "camp14","north", 0, 1);
	reset_room();
}


