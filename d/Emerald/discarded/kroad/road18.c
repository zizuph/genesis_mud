/*
 * road18.c
 * Kahlen Road
 * by Alaron September 17, 1996
 */

#include "defs.h"

inherit BASEROAD;

void
create_road()
{
   set_short("Packed dirt road");
   set_long("   The forest here is thick and overpowering. The treeline "+
	    "seems to push out into the road, almost as if the forest "+
	    "were trying to swallow the dirt path and anything on it. The "+
	    "road continues to the northeast and southwest, travelling "+
	    "by a multitude of low greenery and foliage between it and "+
	    "the forest rim.\n\n");
   
   OUTSIDE;
   LIGHT(1);
   
   add_item( ({"path", "small path", "southeast"}),
	    "There is a small path which branches off of the main "+
	    "road and heads into the forest to the southeast.\n");
   
   add_item( ({"bushes", "low bushes", "foliage", "green foliage",
	       "vegetation", "low greenery", "greenery"}),
	    "The bushes surrounding the raod rustle gently in the "+
	    "cool breeze. There are various forms of plant life, "+
	    "including flowers, weeds, vines, and more. Some even "+
	    "look vaguely familiar.\n");
   
   add_item( ({"flowers", "weeds", "vines"}),
	    "There are several kinds of flowers growing amidst the "+
	    "low green bushes. Some of them even appear familiar.\n");
   
   
   add_exit(PATH + "road17", "northeast", 0, 1);
   add_exit(PATH + "road19", "southwest", 0, 1);
}

