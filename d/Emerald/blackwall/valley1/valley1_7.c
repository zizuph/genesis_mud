/* A valley in the southern Blackwall mountains.

   Code (c) 1999 to Damian Horton - BKA Casimir.
*/
 
#pragma strict_types
#pragma save_binary 

#include "/d/Emerald/sys/paths.h"

inherit BLACKWALL_VALLEY1_DIR + "base_valley.c";

void
create_valley_room()
{
    set_short("Along a small river in the southern portion of the "+
	      "Blackwall mountains.\n");
    set_em_long("Along a small river in the southern portion of the "+
		"Blackwall mountains. The river descends from the "+
		"mountains to the east, and flows into a lush green "+
		"forest to the west. Mountains of black rock "+
		"rise to either side of the river valley.\n");

    set_river_room();

    add_item("sky",
	     "You are afforded a clear view of the sky thanks to the break "+
	     "in the forest afforded by the river.\n");

    add_item(({"forest", "woods", "trees", "canopy"}) ,
	     "A vast expanse of sylvan forest extends as far as the "+
	     "eye can see, to the south and to the west, its green "+
	     "canopy seeming almost luminescent.\n");

    add_item(({"river", "water", "waters", "crystalline surface", "forth",
		 "pockets", "pockets of froth"}),
	     "A swift-flowing river about 20 feet across. The river is deep, "+
	     "its crystalline surface marred by occasional pockets of froth "+
	     "emanating from more turbulent waters upstream.\n");
    
    add_item(({"mountains", "blackwall mountains", "peaks", "black peaks",
		 "cliffs"}),
      "You are at the edge of the southern extreme of the Blackwall "+
      "mountains. A forest of deep black peaks dominates to the North. "+
      "Two mountains loom directly to your west, one on either side "+
      "of the river valley. The northern most one is the taller of the "+
      "two, its jagged peak jutting skyward as if to lacerate the "+
      "clouds. The southern one is much less impressive, standing "+
      "not nearly so tall, and with a flattened top. Still, its face is "+
      "marred by stark black cliffs, and it would be no easy conquest.\n");
    
    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_8", "northeast", 0, 3);
    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_6", "west", 0, 3);
}

void
init()
{
    ::init();
    add_action(drink_from_stream, "drink");
}




