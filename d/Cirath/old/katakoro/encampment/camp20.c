/*
* Created by: 
* Date: 
*
* File: /d/Cirath/katakoro/encampment/camp20.c
* Comments: edited by Luther Sept 2001
*/

#pragma save_binary

inherit "/std/room.c";
#include "defs.h"
#include "/d/Cirath/common/teamer.h"

void
reset_room()
{
	bring_room_team(KAT_NPC + "eguard.c", 1, 3);
}	

void
create_room()
{
   	set_short("Empress' camp");
   	set_long("This is a guard post located outside the yurt of the "+
		"Khahan's wife. Four guards are posted here to ensure the "+
		"security of the area. There is very little activity; "+
		"Only other guards can be seen walking around.\n");

	OUTSIDE;

   	add_exit(KAT_CAMP + "camp19.c", "southeast", 0, 1);
   	add_exit(KAT_CAMP + "camp21", "north", 0, 1);
   	add_exit(KAT_YURTS + "yurt10", "enter", 0, 1, 1);
	reset_room();
}