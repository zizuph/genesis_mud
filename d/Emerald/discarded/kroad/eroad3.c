/*
 * eroad3.c
 * Kahlen Road
 * by Alaron August 31, 1996
 */

#include "defs.h"

inherit BASEROAD;

void
create_road()
{
    set_short("Packed dirt road");
    set_long("   The narrow, packed dirt road leads north and south "+
	     "from here. To the south it heads toward the cliff face "+
	     "overlooking a panoramic ocean view. The vegetation on the "+
	     "east side of the path is low and very green. Further to the "+
	     "east it seems to rise up out of the ground, growing into "+
	     "a forest edge. The western side of the path follows the "+
	     "cliff face, dropping off abruptly after several puddles and "+
	     "patches of mud.\n\n");

    OUTSIDE;
    LIGHT(1);

    add_item( ({"cliffs", "south", "west", "cliff face"}),
	     "The cliffs to the south and to the west drop off abruptly "+
	     "after the ground turns wet, muddy and filled with puddles. A "+
	     "cool sea wind whistles against the cliff, spraying moisture "+
	     "up over the side to collect near the road.\n");

    add_item( ({"bushes", "low bushes", "foliage", "green foliage",
		"vegetation"}),
	     "The vegetation surrounding the path on the east side is "+
	     "low and overgrown, seeming to creep out of the wood and "+
	     "onto the road. Further back to the east it seems to rise out "+
	     "of the ground and melt into the forest edge. Various vines, "+
	     "flowers and other weeds can be seen among the greenery.\n");

    add_item( ({"flowers", "weeds", "vines"}),
	     "A lot of the flowers and weeds in the greenery seem like "+
	     "familiar plant types.\n");

    add_exit(PATH + "eroad2", "north", 0, 1);
    add_exit(PATH + "eroad4", "south", 0, 1);
}
