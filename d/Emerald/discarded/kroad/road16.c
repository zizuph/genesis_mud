/*
 * road16.c
 * Kahlen Road
 * by Alaron September 17, 1996
 */

#include "defs.h"

inherit BASEROAD;

void
create_road()
{
    set_short("Packed dirt road");
    set_long("   The road here is narrow as the forest closes in on it "+
	     "from both sides. The road curves sharply around a huge "+
	     "boulder and heads southeast and southwest from here. The "+
	     "north and south edges of the road are covered with low "+
	     "greenery and bushes which seem to be reaching out toward "+
	     "the road, trying to swallow it. Just past the greenery "+
	     "is the rim of the overwhelming, sprawling forest.\n\n");

    OUTSIDE;
    LIGHT(1);
    

    remove_item("forest");

    add_item( ({"bushes", "low bushes", "foliage", "green foliage",
		"vegetation", "low greenery", "greenery"}),
	     "The bushes surrounding the road rustle gently in the "+
	     "cool breeze. There are various forms of plant life, "+
	     "including flowers, weeds, vines, and more. Some even "+
	     "look vaguely familiar.\n");

    add_item( ({"flowers", "weeds", "vines"}),
	     "There are several kinds of flowers growing amidst the "+
	     "low green bushes. Some of them even appear familiar.\n");

    add_item( ({"forest", "sprawling forest", "enormous forest",
		"overwhelming forest", "trees", "north", "south"}),
	     "The vast forest seems to spread out in all directions "+
	     "on either side of the road, engulfing everything in its "+
	     "path. It is even difficult to see the rest of the road "+
	     "around the high trees. The loud sounds of forest animal "+
	     "life echo across the road.\n");

    add_item( ({"boulder", "huge boulder"}),
	     "The huge boulder sits at the top of the curve in the road "+
	     "where it turns southeast and southwest. It is large enough "+
	     "to block all large traffic but still allow people on foot "+
	     "to squeeze by between it and the forest rim.\n");

    add_exit(PATH + "road15", "southeast", 0, 1);
    add_exit(PATH + "road17", "southwest", 0, 1);
}
