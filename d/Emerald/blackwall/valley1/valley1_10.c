/* A valley in the southern Blackwall mountains.

   Code (c) 1999 to Damian Horton - BKA Casimir.
*/
 
#pragma strict_types
#pragma save_binary 

#include "/d/Emerald/sys/paths.h"
#include "/d/Emerald/sys/weather.h"

inherit BLACKWALL_VALLEY1_DIR + "base_valley.c";

void
create_valley_room()
{
    set_short("Along a small river in the southern portion of the "+
	      "Blackwall mountains.\n");
    set_em_long("Along a small river in the southern portion of the "+
		"Blackwall mountains. The river descends from the "+
		"mountains to the east, and flows into a lush green "+
		"forest to the west. You can hear the roar of a "+
		"waterfall issuing from downstream.\n");

    set_river_room();

    remove_item("sky");
    add_item("sky",
	     "Much of the sky is obscured by the mountains which tower "+
	     "above either side of the valley. " + WEATHER_DESC_SKY + "\n");
	     
    add_item(({"roar", "waterfall", "roar of a waterfall"}),
	     "The sound of a waterfall issues from downstream.\n");

    add_item(({"forest", "sylvan forest", "canopy"}),
	     "A vast expanse of sylvan forest extends as far as the "+
	     "eye can see, to the south and to the west, its green "+
	     "canopy seeming almost luminescent.\n");

    add_item(({"river", "rapids", "water", "precipices", "rock "}),
	     "A swift flowing stream which bubbles and froths as it falls "+
	     "over short precipices and flows around protruding expanses "+
	     "of rock. The water is clear, but cold.\n"); 
    
    add_item(({"mountains", "blackwall mountains", "peak", "peaks",
		 "mountain", "cliff", "cliffs", "forest of black peaks",
		   "forest of peaks", "jagged peak", "flattened top",
		   "vista", "north", "northern vista"}),
      "You are at the edge of the southern extreme of the Blackwall "+
      "mountains. A forest of black peaks dominates the northern vista. "+
      "Two mountains line either side of the valley. The northern one "+
      "is the taller of the "+
      "two, its jagged peak jutting skyward as if to lacerate the "+
      "clouds. The southern one is much less impressive, standing "+
      "not nearly so tall, and with a flattened top. Still, its face is"+
      " marred by stark black cliffs, and it would be no easy conquest.\n");
    
    add_exit("valley1_11", "east", 0, 4);
    add_exit("valley1_9",  "southwest", 0, 4);
}

/* This sterile area has no particular smell to it, therefor the
   default valley function is masked with a blank one. */

public void
hook_smelled(string arg)
{
}

void
init()
{
    ::init();
    add_action(drink_from_stream, "drink");
}




