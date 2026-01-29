/*
* Created by: 
* Date: 
*
* File: /d/Cirath/katakoro/encampment/camp5.c
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
	bring_room_team(KAT_NPC + "kashik", 1, 1);
}

void
create_room()
{
   	set_short("Barbarian camp");
   	set_long("This is at the base of a small hill within the valley.  "+
		"Below and towards the south stretches the entire camp, with only "+
   		"a stockade guarded by two men to the north.\n");

   	add_item("stockade","The wooden posts of this stockade seem to be "+
		"placed more as a decoration than as fortification. While "+
		"certainly capable of blocking entry to individuals, they "+
		"would be no defense against a determined attack.\n");

   	add_exit(KAT_CAMP + "camp4","south", 0, 1);  
   	add_exit(KAT_CAMP + "camp6","north", 0, 1);  
   	add_exit(KAT_CAMP + "camp14","west", 0, 1);  
   	add_exit(KAT_CAMP + "camp11","east", 0, 1);  
	reset_room();
}
  
