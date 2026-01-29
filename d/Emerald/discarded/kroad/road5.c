/*
 * road5.c
 * Kahlen Road
 * by Alaron September 17, 1996
 */

#include "defs.h"

inherit BASEROAD;

void
create_road()
{
    set_short("Packed dirt road");
    set_long("   The hard-packed dirt road follows the edge of the "+
	     "cliff along the coastline. The north side of the road is "+
	     "bordered by a thick cluster of low, green vegetation "+
	     "which eventually gives way to form the rim of an enormous, "+
	     "thick forest. A cool, salty breeze drifts across the road "+
	     "from the ocean inlet below the cliff. The road continues "+
	     "along the cliff side to the east where it forks north and "+
	     "south, and to the east.\n\n");

    OUTSIDE;
    LIGHT(1);
    
    add_item( ({"cliffs", "south", "cliff side"}),
	     "The white and gray cliffs to the south rise up out of the "+
	     "ocean at a steep angle. As the cliffs recede into the "+
	     "mountainside, growth and vegetation begin to appear until "+
	     "farther to the north it escalates into the edge of a "+
	     "forest. As you examine the cliffs, you can "+
	     "hear the sounds of water crashing against the rocks "+
	     "far below.\n");
    
    add_item( ({"bushes", "low bushes", "foliage", "green foliage",
		"vegetation", "low vegetation", "green vegetation"}),
	     "The bushes to the north of the path rustle gently in the "+
	     "cool sea breeze. There are various forms of plant life, "+
	     "including flowers, weeds, vines, and more. Some even "+
	     "look vaguely familiar.\n");

    add_item( ({"flowers", "weeds", "vines"}),
	     "There are several kinds of flowers growing amidst the "+
	     "low green bushes. Some of them even appear familiar.\n");

    add_exit(PATH + "road6", "west", 0, 1);
    add_exit(PATH + "road4", "east", 0, 1);
}

