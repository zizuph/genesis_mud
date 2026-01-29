/*
* Created by: 
* Date: 
*
* File: /d/Cirath/katakoro/encampment/camp7.c
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
	bring_room_team(KAT_NPC + "kashik", 1, 3);
}

void
create_room()
{
    	set_short("Khahan's Stockade");
   	set_long("This is a guard post within the stockade of the "+
		"Khahan. Four kashik guards are posted here to ensure the "+
		"the security of the area. There is very little activity "+
		"within the stockade and only members of the Kashik can be "+
		"seen walking around.\n");

   	add_exit(KAT_CAMP + "camp6","south", 0, 1);  
   	add_exit(KAT_CAMP + "camp10","north", 0, 1);  
   	add_exit(KAT_CAMP + "camp8","east", 0, 1);  
   	add_exit(KAT_CAMP + "camp9","west", 0, 1);  
	reset_room();
}

  
