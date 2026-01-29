/* Woodlands, north of Telberin and south of the Blackwall mountains.
   Code (c) 1999 to Damian Horton - BKA Casimir.
*/
 
#pragma strict_types
#pragma save_binary 

#include "/d/Emerald/sys/paths.h"

inherit BLACKWALL_VALLEY1_DIR + "base_valley.c";

void
create_valley_room()
{
    set_short("Beside a small river, in moderately dense woodlands, north of "+
	      "Telberin.\n");
    set_em_long("Beside a small river, in moderately dense woodlands, north of "+
		"Telberin and south of the Blackwall mountains. The river "+
		"gently winds its way through the forest, flowing from west "+
		"to east. The break in the treeline afforded by the river "+
		"gives one a good view of the Blackwall mountains, which lie "+
		"to the north. You may follow the river upstream, or "+
		"stray towards the more inhabited portions of Emerald by "+
		"heading southwest.\n");

    set_river_room();

    add_item(({"forest", "woods", "woodlands", "trees", "bushes"}),
	     "The forest is relatively thin along the river, though an "+
	     "abundance of bushes grows along its banks.\n");

    add_item(({"view", "break"}),
	     "You get a good view of the Blackwall mountains from this "+
	     "location.\n");

    add_item(({"river", "water"}),
	     "A small river, about 30 feet across. Smooth, clear water "+
	     "flows gently from east to west.\n");

    add_item(({"mountains", "blackwall", "blackwall mountains",
		 "blackwall mountains", "peaks"}),
	     "The foreboding black peaks of the mountains dominate the terrain "+
	     "to the north and east. Wisps of smoke emanate from the highest, "+
	     "and largest mountain, Mount Black.\n");

    add_item("sky",
	     "You are afforded a clear view of the sky thanks to the break "+
	     "in the forest afforded by the river.\n");

    add_item(({"mount black", "volcano"}),  "The dominant mountain of the "+
              "range, it is also an active volcano.\n");

    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_3", "east", 0, 4);
    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_1", "southwest", 0, 4);
}

void
init()
{
    ::init();
    add_action(drink_from_stream, "drink");
}




