/*
 * road3.c
 * Kahlen Road
 * by Alaron September 17, 1996
 */

#include "defs.h"

inherit BASEROAD;

void
create_road()
{
    set_short("Packed dirt road");
    set_long("   The road here turns a corner along the edge of the "+
	     "cliff face as it continues through low vegetation toward "+
	     "the rim of an enormous forest to the north. Low, green "+
	     "foliage here ruffles in the gentle, salty breeze which "+
	     "drifts up from alongside the cliffs, blanketing the road "+
	     "in salty puddles. The road is surrounded on the north "+
	     "side by low vegetation which gives way further north "+
	     "to an enormous forest. The path continues along the "+
	     "cliff side far to the west and to the north.\n\n");

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
		"vegetation", "low vegetation", "low foliage"}),
	     "The bushes to the north of the path rustle gently in the "+
	     "cool sea breeze. There are various forms of plant life, "+
	     "including flowers, weeds, vines, and more. Some even "+
	     "look vaguely familiar.\n");

    add_item( ({"flowers", "weeds", "vines"}),
	     "There are several kinds of flowers growing amidst the "+
	     "low green bushes. Some of them even appear familiar.\n");

    add_exit(PATH + "road2", "north", 0, 1);
    add_exit(PATH + "road4", "west", 0, 1);
}
