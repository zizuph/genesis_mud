/*
* Created by: 
* Date: 
*
* File: /d/Cirath/katakoro/encampment/camp23.c
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
	bring_room_team(KAT_NPC + "guard", 1, 3);
}

void
create_room()
{
     	set_short("Barbarian camp");
  	set_long("This is the outer border of the encampment. Scattered "+
		"about this area are the guards as well as the men in charge "+
		"of the livestock that is grazing nearby. Stubby grass has "+
		"begun breaking through the pitted crust of old snow, and the "+
		"ground is beginning to thaw and become muddy.\n");

  	add_exit(KAT_CAMP + "camp18","west", 0, 1);  
  	add_exit(KAT_DES + "steppe1","south", 0, 1);
	reset_room();
}
  
