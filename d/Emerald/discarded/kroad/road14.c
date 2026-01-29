/*
 * road14.c
 * Kahlen Road
 * by Alaron September 17, 1996
 */

#include "defs.h"

inherit BASEROAD;

void
create_road()
{
    set_short("Packed dirt road");
    set_long("   The hard-packed forest road curves northwest away from "+
	     "the ocean cliffs to the south here. An enormous, sprawling "+
	     "forest runs along the edge of the road on the north side "+
	     "just beyond the patches of low, thriving greenery. The cool, "+
	     "salt breeze drifts across the road, flowing up from the "+
	     "ocean inlet to the south far below the cliffs. The road "+
	     "continues to the northwest and east.\n\n");

    OUTSIDE;
    LIGHT(1);
    
    add_item( ({"cliffs", "south"}),
	     "The white and gray cliffs to the south rise up out of the "+
	     "ocean at a steep angle. As the cliffs recede into the "+
	     "mountainside, growth and vegetation begin to appear until "+
	     "farther to the north it escalates into the edge of a "+
	     "forest. As you examine the cliffs, you can "+
	     "hear the sounds of water crashing against the rocks "+
	     "far below.\n");

    add_item( ({"bushes", "low bushes", "foliage", "green foliage",
		"vegetation", "low greenery", "greenery"}),
	     "The bushes to surrounding the road rustle gently in the "+
	     "cool sea breeze. There are various forms of plant life, "+
	     "including flowers, weeds, vines, and more. Some even "+
	     "look vaguely familiar.\n");

    add_item( ({"flowers", "weeds", "vines"}),
	     "There are several kinds of flowers growing amidst the "+
	     "low green bushes. Some of them even appear familiar.\n");
    
    add_exit(PATH + "road13", "east", 0, 1);
    add_exit(PATH + "road15", "northwest", 0, 1);
}
