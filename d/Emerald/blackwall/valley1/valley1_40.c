/* Woodlands south of the Blackwall mountains.

   Code (c) 1999 to Damian Horton - BKA Casimir.
*/

#pragma strict_types
#pragma save_binary 

#include "/d/Emerald/sys/paths.h"
#include <stdproperties.h>

inherit BLACKWALL_VALLEY1_DIR + "base_valley.c";

void
create_valley_room()
{
    set_short("On a talus slope.");
    set_em_long("At the base of an impossibly high cliff. The cliff " +
		"extends nearly to the pinnacle of the mountain, "+
		"perhaps 300 metres above you. An extensive talus "+
		"slope leads down the mountain to the southeast, "+
		"while you can travel along the cliff face to the "+
		"south.\n");

    add_prop(ROOM_I_HIDE, 25); //little cover
    
    add_item(({"blackwall", "blackwall mountains", "mountains", "range",
		 "Blackwall range"}),
	    "To the north extend the Blackwall mountains, as far "+
	    "as your eye can see, their black forms piercing skyward "+
	    "as if in mockery of the Heavens.\n");

    add_item("mountain",
	     "You on the lower slopes of a mountain, the upper "+
	     "reaches of which are dominated by masses of black "+
	     "cliffs.\n");
 
    add_item(({"cliff", "black cliff", "cliffs", "black cliffs",
		 "cliff face"}),
	     "The cliff is composed of jagged black basalt. The "+
	     "sheer height of the cliff makes climbing it unthinkable.\n");

    add_item(({"talus", "debris", "talus slope", "boulders", "ground",
		 "down", "grass", "bushes", "tufts of grass"}),
	     "You are standing at the top of an orderly collection "+
	     "of debris which has fallen off of the cliff over the "+
	     "centuries. The size of the boulders grows progressivly "+
	     "larger with distance from the cliff face. Tufts of grass "+
	     "and small bushes suggest that both the slope and the "+
	     "cliff have been stable for sometime.\n");

    add_cmd_item(({"cliff", "cliff face"}), ({"climb", "climb up",
						"climb up the"}),
       "You would never manage to climb a cliff of that height "+
       "without the aid of equipment!\n");

    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_28", "southwest", 0, 7);
    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_39", "south", 0, 7);
}

/* This sterile area has no particular smell to it, therefor the
   default valley function is masked with a blank one. */

public void
hook_smelled(string arg)
{
}

 





