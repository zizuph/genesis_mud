/*
 * road9.c
 * Kahlen Road
 * by Alaron September 17, 1996
 */

#include "defs.h"

inherit BASEROAD;

void
create_road()
{
    set_short("Packed dirt road");
    set_long("   The packed road here runs parallel to the edge of an "+
	     "enormous forest on its northern edge. Low, green foliage "+
	     "runs rampant along the edges of the road, reaching toward "+
	     "it as if in seek of further nutrients. Beyond the road "+
	     "to the south, across the low greenery, you can see the "+
	     "cliffs and hear the sound of water crashing against rock. The "+
	     "road here continues to the east and west along the forest "+
	     "edge.\n\n");

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
		"vegetation", "low vegetation", "low greenery",
		"greenery"}),
	     "The bushes surrounding the road rustle gently in the "+
	     "cool sea breeze. There are various forms of plant life, "+
	     "including flowers, weeds, vines, and more. Some even "+
	     "look vaguely familiar.\n");

    add_item( ({"flowers", "weeds", "vines"}),
	     "There are several kinds of flowers growing amidst the "+
	     "low green bushes. Some of them even appear familiar.\n");

    add_exit(PATH + "road10", "west", 0, 1);
    add_exit(PATH + "road8", "east", 0, 1);
}
