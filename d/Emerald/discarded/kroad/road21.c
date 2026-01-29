/*
 * road21.c
 * Kahlen Road
 * by Alaron September 17, 1996
 */

#include "defs.h"

inherit BASEROAD;

void
create_road()
{
    set_short("Packed dirt forest road");
    set_long("   A cool, moist breeze blows across the road from the "+
	     "north, whistling against the trees and continuing "+
	     "south. The forest here is incredibly thick and seems to "+
	     "push in upon the road, almost as if it were trying to "+
	     "swallow it whole. A thick layer of low greenery fills "+
	     "the narrow gap between the edges of the road and the "+
	     "forest treeline. The road here continues to the north "+
	     "and comes to an abrupt halt in a large clearing to the "+
	     "south.\n\n");

    OUTSIDE;
    LIGHT(1);
    
    remove_item("forest");

    add_item("forest",
	     "The forest here is thick and overwhelming, its incredible "+
	     "treeline seemingly bulging out on to the road, threatening "+
	     "to swallow it whole.\n");
    
    add_item( ({"bushes", "low bushes", "foliage", "green foliage",
		"vegetation", "greenery", "low greenery"}),
	     "The bushes surrounding the road rustle gently in the "+
	     "cool breeze. There are various forms of plant life, "+
	     "including flowers, weeds, vines, and more. Some even "+
	     "look vaguely familiar.\n");

    add_item( ({"flowers", "weeds", "vines"}),
	     "There are several kinds of flowers growing amidst the "+
	     "low green bushes. Some of them even appear familiar.\n");

    add_item( ({"clearing", "large clearing", "south"}),
	     "The forest pulls back from the road a bit to the south, "+
	     "and dead-ends, forming a large clearing.\n");

    add_exit(PATH + "road20", "north", 0, 3);
    add_exit(PATH + "road22", "south", 0, 3);
}
