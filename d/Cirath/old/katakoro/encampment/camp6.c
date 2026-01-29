/*
* Created by: 
* Date: 
*
* File: /d/Cirath/katakoro/encampment/camp6.c
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
     	set_short("Barbarian camp");
   	set_long("Midway up this small hill within the valley stands a "+
		"large gate, the only noticable entry into the stockade "+
		"beyond. Four Kashiks stand guard, allowing only those "+
		"worthy of the Khahan's time to pass.\n");

   	add_item("gate","This gate is mostly a formal affair as it really "+
		"could not stand up to a determined assault.\n");

   	add_exit(KAT_CAMP + "camp5","south", 0, 1);  
   	add_exit(KAT_CAMP + "camp7","north", 0, 1);  
	reset_room();
}
  
