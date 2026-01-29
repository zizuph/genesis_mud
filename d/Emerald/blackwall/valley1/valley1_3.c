/* Woodlands south of the Blackwall mountains.

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
    set_em_long("Along a small river, in moderately dense woodlands, north of "+
		"Telberin and south of the Blackwall mountains. The river "+
		"meanders its way down from the Blackwall mountains to "+
		"the east.\n");

    set_river_room();

    add_item("sky",
	     "You are afforded a clear view of the sky thanks to the break "+
	     "in the forest afforded by the river.\n");

    add_item(({"forest", "woods", "woodlands", "trees"}),
	     "The forest is relativly thin along the river, with an abundance "+
	     "of bushes growing along the banks. The woods team with life.\n");

    add_item(({"life", "animals", "birds"}),
	    "Of all the creatures of these woodlands, birds appear to be the "+
	    "most numerous. The sound of their chirping fills the air "+
	    "constantly and there seems to be no end to the multiplicity of "+
	    "sounds, sizes, and colors they display.\n");

    add_item(({"river", "water"}),
	     "A small river, about 30 feet across. The smooth, clear water "+
	     "flows gently from east to west.\n");

    add_item(({"mountains", "blackwall", "blackwall mountains"}),
	     "The foreboding black peaks of the mountains dominate the terrain "+
	     "to the north and west. Wisps of smoke emanate from the highest, "+
	     "and largest mountain, Mount Black.\n");

    add_item(({"mount Black", "volcano"}), "The dominant mountain of the "+
             "range, it is also an active volcano.\n");

    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_4", "east", 0, 3);
    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_2", "west", 0, 3);
}

void
init()
{
    ::init();
    add_action(drink_from_stream, "drink");
}




