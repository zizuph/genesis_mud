/*
* Created by: 
* Date: 
*
* File: /d/Cirath/katakoro/encampment/camp8.c
* Comments: edited by Luther Sept 2001
*/

inherit "/std/room.c";
#include "defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Cirath/common/teamer.h"

void
reset_room()
{
	bring_room_team(KAT_NPC + "kashik", 1, 4);
}

void
create_room()
{
   	set_short("Khahan's Stockade");
   	set_long("This area within the Khahan's stockade has been given to "+
		"his bodyguards, the Kashik. There is a large cooking fire "+
		"here, around which some of the kashik are standing. To the "+
		"northwest is a large yurt, probably quarters for the men that "+
		"aren't currently on duty.\n");

   	add_exit(KAT_CAMP + "camp7", "east", 0, 1);
  	add_exit(KAT_YURTS + "yurt4", "enter", 0, 1, 1);
	reset_room();
}

  
