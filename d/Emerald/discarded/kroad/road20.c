/*
 * road20.c
 * Kahlen Road
 * by Alaron September 20, 1996
 */

#include "defs.h"

inherit BASEROAD;

void
create_road()
{
    set_short("Packed dirt road");
    set_long("   The forest seems to creep in on the road, as if it were "+
	     "attempting to swallow the thing whole. A thick layer of "+
	     "low greenery blows gently in the cool breeze between the "+
	     "edge of the road and the rim of the immense forest. The road "+
	     "here winds its way to the north and south.\n\n");
    
    OUTSIDE;
    LIGHT(1);

    remove_item("forest");

    add_item( ({"forest", "immense forest"}),
	     "The immense forest seems to surround the road on both "+
	     "sides, bulging outward toward it, almost as if it were "+
	     "trying to swallow the road within its borders.\n");

    add_item( ({"bushes", "low bushes", "foliage", "green foliage",
		"vegetation", "low greenery","greenery"}),
	     "The bushes surrounding the road rustle gently in the "+
	     "cool breeze. There are various forms of plant life, "+
	     "including flowers, weeds, vines, and more. Some even "+
	     "look vaguely familiar.\n");

    add_item( ({"flowers", "weeds", "vines"}),
	     "There are several kinds of flowers growing amidst the "+
	     "low green bushes. Some of them even appear familiar.\n");

    add_exit(PATH + "road19", "north", 0, 3);
    add_exit(PATH + "road21", "south", 0, 3);
}
