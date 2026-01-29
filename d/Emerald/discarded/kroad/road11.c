/*
 * road11.c
 * Kahlen Road
 * by Alaron September 17, 1996
 */

#include "defs.h"

inherit BASEROAD;

void
create_road()
{
    set_short("Packed dirt road");
    set_long("   The hard-packed dirt road rounds a soft corner here. It "+
	     "extends up to the north where it runs along the rim of "+
	     "an enormous, thick forest. Between the road and the forest "+
	     "is a large patch of thriving, low foliage, nearly covering "+
	     "the sides of the road. Further to the south, beyond the "+
	     "low greenery, you can see the cliffs and hear the sound "+
	     "of water crashing against rock.\n\n");

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
		"vegetation", "low greenery", "greenery",
		"low foliage"}),
	     "The bushes surrounding the path rustle gently in the "+
	     "cool sea breeze. There are various forms of plant life, "+
	     "including flowers, weeds, vines, and more. Some even "+
	     "look vaguely familiar.\n");

    add_item( ({"flowers", "weeds", "vines"}),
	     "There are several kinds of flowers growing amidst the "+
	     "low green bushes. Some of them even appear familiar.\n");

    add_exit(PATH + "road12", "west", 0, 1);
    add_exit(PATH + "road10", "north", 0, 1);
}
