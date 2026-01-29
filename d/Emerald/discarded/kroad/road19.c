/*
 * road19.c
 * Kahlen Road
 * by Alaron September 17, 1996
 */

#include "defs.h"

inherit BASEROAD;

void
create_road()
{
    set_short("Packed dirt road");
    set_long("   The forest here seems to press in the road, almost as if "+
	     "it were trying to swallow the packed dirt and anything "+
	     "on it. A cool, gentle breeze drifts through the corridor-like "+
	     "path formed by the treeline of the forest on both sides "+
	     "of the road. The road continues to the northeast and to "+
	     "the south, following a narrow course through the thick "+
	     "forest. A layer of low, thriving greenery separates the "+
	     "road from the actual rim of the forest.\n\n");

    OUTSIDE;
    LIGHT(1);
    
    remove_item("forest");

    add_item( ({"forest", "thick forest", "enormous forest"}),
	     "The thick, sprawling forest seems to surround the "+
	     "narrow road on both sides, almost as if it were pushing "+
	     "in on the road in an attempt to swallow it whole. The "+
	     "effect is quite eerie. The forest allows the road enough "+
	     "room to continue to the northeast and the south.\n");

    add_item( ({"bushes", "low bushes", "foliage", "green foliage",
		"vegetation", "greenery", "thriving greenery"}),
	     "The bushes surrounding the path rustle gently in the "+
	     "cool breeze. There are various forms of plant life, "+
	     "including flowers, weeds, vines, and more. Some even "+
	     "look vaguely familiar.\n");

    add_item( ({"flowers", "weeds", "vines"}),
	     "There are several kinds of flowers growing amidst the "+
	     "low green bushes. Some of them even appear familiar.\n");

    add_exit(PATH + "road18", "northeast", 0, 3);
    add_exit(PATH + "road20", "south", 0, 3);
}
