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
    set_short("Base of a talus slope.");
    set_em_long("At the base of a talus slope upon a mountain. "+
		"The slope is composed of large boulders of black "+
		"rock which are clearly stable, for a number of "+
		"young trees have already grown for several years "+
		"amongst them. Nonetheless, traversing the talus slope "+
		"is treacherous.\n");

    add_prop(ROOM_I_HIDE, 20); //little cover

    add_item(({"mountains", "blackwall", "blackwall mountains",
		   "peaks", "range", "blackwall range"}),
	    "You are at the southern end of the Blackwall mountains. "+
	    "The mountains are taller, and less inviting to "+
	    "the north.\n");

    add_item(({"mountain", "east mountain", "lesser peak", "peak",
		 "near mountain"}),
	     "You on the lower slopes of a mountain, the upper "+
	     "reaches of which are dominated by masses of black "+
	     "cliffs. Such a cliff can be found at the top of "+
	     "the talus slope.\n");

    add_item(({"cliff", "black cliff", "cliffs", "black cliffs"}),
	     "Stretches of hundred or more metre tall cliffs "+
	     "dominate much of the mountainside. They do not appear "+
	     "climbable.\n");

    add_item(({"talus", "debris", "talus slope", "boulders",
		 "ground", "down"}),
	     "The base of the talus slope consists of the largest "+
	     "boulders to slide off of the mountain over the past "+
	     "several centuries. Some of them reach as large as "+
	     "three metres in diamater. All are composed of the "+
	     "black basalt which makes up the majority of the "+
	     "mountain range.\n");

    add_item(({ "trees", "young trees"}),
	     "You notice that it is evergreens, pines in "+
	     "particular which have managed to root themselves "+
	     "amongst the boulders.\n");
 
    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_27", "southwest", 0, 4);
    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_40", "northeast", 0, 7);
}

/* This sterile area has no particular smell to it, therefor the
   default valley function is masked with a blank one. */

public void
hook_smelled(string arg)
{
}

 





