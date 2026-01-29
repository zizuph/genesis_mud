/* Woodlands south of the Blackwall mountains.

   Code (c) 1999 to Damian Horton - BKA Casimir.
*/
 
#pragma strict_types
#pragma save_binary 

#include "/d/Emerald/sys/paths.h"
#include <macros.h>

inherit BLACKWALL_VALLEY1_DIR + "base_valley.c";

/* Called when a player exits to the northeast (fording the stream).
 */
int
ford_fun()
{
    write("You wince upon first contact with the icy water, but force "+
	  "yourself to cross the stream. You then scramble up the "+
	  "opposite bank and into the forest beyond.\n");

    say(QCTNAME(this_player()) + " wades across the stream.\n");
    return 0;
}

void
create_valley_room()
{
    set_short("Beside a small river, in moderately dense woodlands, north of "+
	      "Telberin.\n");
    set_em_long("Along a small river, in moderately woodlands, north of "+
		"Telberin and south of the Blackwall mountains. The river "+
		"runs shallow here and could be easily forded.\n");

    set_river_room();

    add_item("sky",
	     "You are afforded a clear view of the sky thanks to the break "+
	     "in the forest afforded by the river.\n");

    add_item(({"forest", "woods", "woodlands", "trees"}),
	     "The forest is relativly thin along the river, and teaming with life.\n");

    add_item(({"animals", "life", "small animals"}),
	     "The songs of a myriad bird species echo all around you while "+
	     "you are regularly afforded a view of small woodlands animals: "+
	     "squirrels, chipmunks, hares, foxes and many others.\n");

    add_item(({"river", "rocks", "water", "riverbed"}),
	     "A small river, about 20 feet across, and only a couple of feet in "+
	     "depth. As a consequence of the shallowness, the water runs swiftly here, "+
	     "frothing vigorously around the larger rocks which dot the riverbed.\n");

    add_item(({"mountains", "blackwall", "blackwall mountains", "peaks"}),
	     "The foreboding black peaks of the mountains dominate the terrain "+
	     "to the north and west. Wisps of smoke emanate from the highest, "+
	     "and largest mountain, Mount Black.\n");

    add_item(({"mount black", "volcano"}), "The dominant mountain of the range,"+
            "it is also an active volcano.\n");

    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_5", "east", 0, 3);
    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_3", "west", 0, 3);
    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_18", "northeast", ford_fun(), 3); 
}

void
init()
{
    ::init();
    add_action(drink_from_stream, "drink");
}




