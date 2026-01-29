/*
* Created by: 
* Date: 
*
* File: /d/Cirath/katakoro/encampment/camp10.c
* Comments: edited by Luther Sept 2001
*/


inherit "/std/room.c";
#include "defs.h"
#include "/d/Cirath/common/teamer.h"

void
reset_room()
{
	bring_room_team(KAT_NPC + "kashik", 1, 1);
}

void
create_room()
{ 
   	set_short("Khahan's Stockade");
   	set_long("This area is right outside of the Khahan's yurt.  There are "+
		"two members of the Kashik standing here as a final guard before "+
		"the entrance.  Also outside the entrance is a tall pole which "+
		"looks like a standard of some sorts.\n");

  	add_item(({"pole","standard"}),"This pole stands nearly 15 feet tall "+
		"and has a crossbrace at the top and from the arms of the brace"+
		"hang black horsetail plums.  Sitting atop the pole is a skull, "+
		"under which hangs a golden plaque.  At the base of the standard "+
		"sit small dolls made of red cloth.\n");
   	add_item("dolls","These small dolls look vaguely humanoid and have "+
		"bits of hair and leather stuck all about them.\n");

   	add_exit(KAT_CAMP + "camp7","south", 0, 1);
  	add_exit(KAT_YURTS + "yurt6","enter", 0, 1, 1);
	reset_room();
}

  
