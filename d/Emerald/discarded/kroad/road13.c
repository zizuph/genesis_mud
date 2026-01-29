/*
 * road13.c
 * Kahlen Road
 * by Alaron September 17, 1996
 */

#include "defs.h"

inherit BASEROAD;

void
create_road()
{
    set_short("Packed dirt road");
    set_long("   The cool, ocean air drifts across the hard-packed dirt "+
	     "road, gently pushing against the low, green foliage "+
	     "which borders the road. Beyond the greenery is the rim "+
	     "of a vast, sprawling forest. The road continues to the "+
	     "north and west, following the edge of the forest on one "+
	     "side and the sheer drop-off of the ocean cliffs on the "+
	     "other.\n\n");

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
		"vegetation", "low foliage"}),
	     "The bushes surrounding the road rustle gently in the "+
	     "cool sea breeze. There are various forms of plant life, "+
	     "including flowers, weeds, vines, and more. Some even "+
	     "look vaguely familiar.\n");

    add_item( ({"flowers", "weeds", "vines"}),
	     "There are several kinds of flowers growing amidst the "+
	     "low green bushes. Some of them even appear familiar.\n");

    add_exit(PATH + "road14", "west", 0, 1);
    add_exit(PATH + "road12", "north", 0, 1);
}
