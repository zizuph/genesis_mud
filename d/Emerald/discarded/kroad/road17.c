/*
 * road17.c
 * Kahlen Road
 * by Alaron September 17, 1996
 */

#include "defs.h"

inherit BASEROAD;

void
create_road()
{
    set_short("Packed dirt path");
    set_long("   The forest here is overwhelming. It seems to push out "+
	     "from the rim and almost try and swallow up the small, "+
	     "narrow dirt road. A cool breeze blows lengthwise through "+
	     "the corridor-like path between the forest created by "+
	     "the thick treeline, brushing up against low greenery "+
	     "and bushes which border the forest edge. The road continues "+
	     "to the southwest and northeast from here.\n\n");
    OUTSIDE;
    LIGHT(1);
    
    add_item( ({"bushes", "low greenery", "greenery", "vegetation",
		"low vegetation", "low bushes"}),
	     "The bushes surrounding the path rustle gently in the "+
	     "cool breeze. There are various forms of plant life, "+
	     "including flowers, weeds, vines, and more. Some even "+
	     "look vaguely familiar.\n");

    add_item( ({"flowers", "weeds", "vines"}),
	     "There are several kinds of flowers growing amidst the "+
	     "low green bushes. Some of them even appear familiar.\n");

    add_exit(PATH + "road16", "northeast", 0, 1);
    add_exit(PATH + "road18", "southwest", 0, 1);
}
