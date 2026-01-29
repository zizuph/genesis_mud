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

    set_short("Light forest.");
    set_em_long("Light forest, not far from the southern portion of the "+
		"Blackwall mountains. The fresh scent of pines fills "+
		"the air. The mountains rise to the north, and to the "+
		"west, while you could descend into increasingly dense "+
		"forest by heading southeast.\n");
 
    add_prop(ROOM_I_HIDE, 20);

    add_item(({"forest", "sylvan forest", "lush forest"}),
	     "Thick sylvan forest streches as far as the ocean to the "+
	     "southeast.\n");

    add_item(({"trees", "tree", "conifer", "conifers", "pines", "pine",
		 "red pines", "jack pines", "vegetation"}),
	     "Red and jack pine seem to be the predominant tree species "+
	     "growing in the immediate shadow of the mountains.\n");
   
    add_item(({"mountains", "blackwall", "blackwall mountains", "peaks",
		 "further peaks", "mount black"}),
	     "Tall peaks of black rock just skyward to the northeast. The "+
	     "further peaks are taller than the nearer ones. Mount Black, "+
	     "a large and active volcano stands out from the rest of the "+
	     "mountains.\n");
	    	     
    add_item(({"rocks", "rock", "black rock"}),
	     "The mountains are made of a coal-black basalt.\n");

    add_item(({"ocean"}),
	     "The barest hint of an endless ocean can be glimpsed "+
	     "beyond the lush forests to the east.\n");

    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_45", "west", 0, 4);
    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_47", "southeast", 0, 4);
}

/* This sterile area has no particular smell to it, therefor the
   default valley function is masked with a blank one. */

public void
hook_smelled(string arg)
{
  if ((! strlen(arg)) || parse_command(arg, ({}), "[the] 'trees' / 'pines' "+
				      "/'pine trees' / 'red pines' / "+
				      "'jack pines' / 'conifers'"))
    {
	write("The fresh scent of pine trees pervades the near mountain "+
	      "air.\n");
    }
}






