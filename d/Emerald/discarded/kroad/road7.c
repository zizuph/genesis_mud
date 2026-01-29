/*
 * road7.c
 * Kahlen Road
 * by Alaron September 17, 1996
 */

#include "defs.h"

inherit BASEROAD;

void
create_road()
{
    set_short("Packed dirt road");
    set_long("   The cool, salt breeze from the ocean inlet far below the "+
	     "cliffs blows across the path, gently brushing against the "+
	     "low, green vegetation and foliage which border the road "+
	     "on the east and west edge. To the north the path continues "+
	     "on toward a thick forest. The sound of waves crashing against "+
	     "the base of the cliffs can be heard far below to the "+
	     "south.\n\n");

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
		"vegetation", "low vegetation", "low foliage",
              }),
	     "The bushes to the north of the path rustle gently in the "+
	     "cool sea breeze. There are various forms of plant life, "+
	     "including flowers, weeds, vines, and more. Some even "+
	     "look vaguely familiar.\n");
    
    add_item( ({"flowers", "weeds", "vines"}),
	     "There are several kinds of flowers growing amidst the "+
	     "low green bushes. Some of them even appear familiar.\n");
    
    add_exit(PATH + "road6", "north", 0, 1);
}
