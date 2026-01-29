/*
 * road15.c
 * Kahlen Road
 * by Alaron September 17, 1996
 */

#include "defs.h"

inherit BASEROAD;

void
create_road()
{
    set_short("Packed dirt road");
    set_long("   The hard-packed dirt road is shadowed and dark here. The "+
	     "enormous, thick forest now borders the road on both sides; "+
	     "the sound of water crashing against the cliffs to the south "+
	     "is now only a faint whisper behind the loud echoing of the "+
	     "sounds of forest animals to the southwest. The road continues "+
	     "on to the northwest and southeast. Beyond the low greenery "+
	     "and bushes bordering the road, to the southeast you can "+
	     "see glimpses of the distant cliffs.\n\n");
    
    OUTSIDE;
    LIGHT(1);
    
    add_item( ({"cliffs", "southeast"}),
	     "You can't make out much more than the faint outlines of "+
	     "the cliffs as the surrounding forest blocks most of "+
	     "your view.\n");
    
    add_item( ({"bushes", "low bushes", "foliage", "green foliage",
		"vegetation", "low greenery"}),
	     "The bushes to surrounding the road rustle gently in the "+
	     "cool breeze. There are various forms of plant life, "+
	     "including flowers, weeds, vines, and more. Some even "+
	     "look vaguely familiar.\n");
    
   add_item( ({"flowers", "weeds", "vines"}),
	    "There are several kinds of flowers growing amidst the "+
	    "low green bushes. Some of them even appear familiar.\n");
        
    add_exit(PATH + "road14", "southeast", 0, 1);
    add_exit(PATH + "road16", "northwest", 0, 1);
}

