/*
 * eroad13.c
 * Kahlen Road
 * by Alaron September 1, 1996
 */

#include "defs.h"

inherit BASEROAD;

void
create_road()
{
    set_short("Misty, coastal road");
    set_long("   You stand amidst a bank of thick, lingering fog. The "+
	     "mist seems to hang ominously over the road, suppressing "+
	     "all light and noise; stifling the surroundings. The "+
	     "ocean inlet is barely visible through the mist to the "+
	     "north beyond the cliff face. Dark, low greenery grows "+
	     "in abundance on all sides of the road, eventually giving "+
	     "way to an enormous, sprawling forest. To the south, you "+
	     "can make out almost no detail except that the road "+
	     "disappears behind another veil of mist.\n\n");

    OUTSIDE;
    LIGHT(1);
    
    add_item( ({"mist", "fog", "veil", "veil of mist", "thick fog",
		"lingering fog"}),
	     "The thick, lingering fog looms ominously over the entire "+
	     "area, creating a stifled, eerie quiet with no noise save "+
	     "for the soft crashing of the waves against the cliff face "+
	     "to the north.\n");

    add_item( ({"cliffs", "north", "inlet", "ocean inlet"}),
	     "You can barely see the ocean inlet to the north through "+
	     "the thick bank of fog.\n");

    add_item( ({"bushes", "low bushes", "foliage", "green foliage",
		"vegetation", "low greenery", "greenery"}),
	     "The dark, low greenery growing in abundance around the "+
	     "road seems to reach toward the water. Among the greenery "+
	     "you notice several kinds of familiar flowers and weeds.\n");

    add_item( ({"flowers", "weeds"}),
	     "Several kinds of the flowers and weeds appear very "+
	     "familiar to you.\n");


    add_exit(PATH + "eroad12", "east", 0, 1);
    add_exit(PATH + "church/steps", "south", 0, 1);
}
