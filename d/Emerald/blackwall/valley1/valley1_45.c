/* A valley in the southern Blackwall mountains.
   Code (c) 2000 to Damian Horton - BKA Casimir.
*/
 
#pragma strict_types
#pragma save_binary 

#include "/d/Emerald/sys/paths.h"
#include <stdproperties.h>
#include "/d/Emerald/sys/weather.h"

inherit BLACKWALL_VALLEY1_DIR + "base_valley.c";

void
create_valley_room()
{
    ::create_valley_room();

    set_short("Valley entrance.");
    set_em_long("At the base of the blackwall mountains. You are at the "+
		"entrance to a valley which leads deeper into the "+
		"mountains. The landscape is rocky, and sparsely vegetated "+
		"but becomes much more lush to the east as you descend "+
		"from the mountains.\n");

    set_highvalley_room();
 
    add_prop(ROOM_I_HIDE, 20);

    add_item(({"vegetation", "bushes", "grasses", "moss"}),
	     "Bushes, grasses, moss and the occasional conifer dot the "+
	     "landscape.\n");

    add_item(({"trees", "tree", "conifer", "conifers", "pines", "pine",
		 "red pines", "jack pines"}),
	     "Red and jack pine seem to be the predominant tree species "+
	     "growing in this area.\n");

    add_item(({"valley"}),
	     "To the northwest, a wide valley winds its way into into "+
	     "the mountains. The valley divides them, isolating "+
	     "a handful of small mountains from the main mass.\n");
    
    add_item(({"mountains", "blackwall", "Blackwall", "blackwall mountains",
		 "tall peaks", "range", "main range", "mass", "main mass"}),
	     "Tall peaks of black rock make up the Blackwall mountains. "+
	     "The main range is north of the valley, while only a few "+
	     "small mountains lie south of it.\n");

    add_item(({"small mountains", "isolated mountains"}),
	     "A few isolated, relatively small mountains lie to the south "+
	     "of the valley.\n");
	    	     
    add_item(({"rocks", "rock", "black rock"}),
	     "The mountains are made of a coal-black basalt.\n");

    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_46", "east", 0, 4);
    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_44", "northwest", 0, 4);
}

/* This sterile area has no particular smell to it, therefor the
   default valley function is masked with a blank one. */

public void
hook_smelled(string arg)
{
}






