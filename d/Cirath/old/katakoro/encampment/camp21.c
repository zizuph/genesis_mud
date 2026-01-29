/*
* Created by: 
* Date: 
*
* File: /d/Cirath/katakoro/encampment/camp21.c
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
	bring_room_team(KAT_NPC + "eguard", 1, 1);
}

void
create_room()
{
      	set_short("Empress' camp");
   	set_long("This area is right outside of the Empress' yurt. There are "+
		"two members of her guard standing here before final entrance "+
		"to her home. Also outside the entrance is a tall pole which "+
		"looks like a standard of some sorts.\n");

  	add_item(({"pole","standard"}),"This pole stands nearly 15 feet tall "+
		"and has a crossbrace at the top and from the arms of the brace"+
		"hang white horsetail plums.\n");

   	add_exit(KAT_CAMP + "camp20","south", 0, 1);
   	add_exit(KAT_YURTS + "yurt11","enter", 0, 1, 1);
	reset_room();
}

  
