/*
* Created by: 
* Date: 
*
* File: /d/Cirath/katakoro/encampment/camp17.c
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
   	set_long("The frequency of yurts, as well as people has decreased "+
		"as this path wanders further away from the encampment. Dark "+
		"scars from old gullies make jagged scars across the ground "+
		"here. Small clumps of bright blue and pink, blooms of early "+
		"crocus and dwarf lily struggle against the sharp cold.\n");

  	add_exit(KAT_CAMP + "camp11","west", 0, 1);  
  	add_exit(KAT_CAMP + "camp18","east", 0, 1);
	reset_room();
}

