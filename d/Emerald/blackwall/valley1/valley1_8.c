/* A valley in the southern Blackwall mountains.
   
   Code (c) 1999 to Damian Horton - BKA Casimir.
*/
 
#pragma strict_types
#pragma save_binary 

#include "/d/Emerald/sys/paths.h"

inherit BLACKWALL_VALLEY1_DIR + "base_valley";

void
create_valley_room()
{
    set_short("Along a small river in the southern portion of the "+
	      "Blackwall mountains.\n");
    set_em_long("Along a small river in the southern portion of the "+
		"Blackwall mountains. The river descends from the "+
		"mountains to the east, and flows into a lush green "+
		"forest to the west. It is marred by rapids, and you "+
		"think you can make out the roar of falling water, "+
		"coming from the northeast. Mountains of black rock "+
		"rise to either side of the river valley.\n");
	
    set_river_room();

    add_item(({"forest", "sylvan forest", "canopy"}),
	     "A vast expanse of sylvan forest extends as far as the "+
	     "eye can see, to the south and to the west, its green "+
	     "canopy seeming almost luminescent.\n");
    
    add_item("sky",
	     "The mountains are not yet so close as to obscure your "+
	     "view of it.\n");

    add_item(({"river", "rapids", "water", "precipices", "rock"}),
	     "A swift flowing stream which bubbles and froths as it falls "+
	     "over short precipices and flows around protruding expanses "+
	     "of rock. The water is clear, but cold.\n"); 
    
    add_item(({"mountains", "blackwall mountains", "peaks", "cliffs",
		 "mountain"}),
	     "You are at the edge of the southern extreme of the Blackwall "+
	     "mountains. A forest of deep black peaks dominates to the North. "+
	     "Two mountains loom directly to your west, one on either side "+
	     "of the river valley. The northern most one is the taller of the "+
	     "two, its jagged peak jutting skyward as if to lacerate the "+
	     "clouds. The southern one is much less impressive, standing "+
	     "not nearly so tall, and with a flattened top. Still, its face is "+
	     "marred by stark black cliffs, and it would be no easy conquest.\n");

    
    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_9", "east", 0, 3);
    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_7", "southwest", 0, 3);
}

void
init()
{
    ::init();
    add_action(drink_from_stream, "drink");
}




