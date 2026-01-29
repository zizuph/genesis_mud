/*
 * 1k10.c
 * This is the bottom of the stairs leading up to the second
 * floor of Castle Telberin.
 * Original re-work by Jasmine
 * Update, New description by Alaron August 16, 1996
 */

#include "default.h"

inherit CASTLE_ROOM;

void
create_room()
{
    ::create_room();
   set_short("Stairwell");
   set_long("   Standing at the foot of a large, marble stairwell, you "+
	    "look up into the hall at the dimly illuminated walls. They "+
	    "are decorated with large tapestries, hung evenly halfway "+
	    "up the stairs as it takes a slight turn around a bend in "+
	    "the wall. Along the stairwell, as it climbs up into the dim "+
	    "light of the second floor of Castle Telberin, there are "+
	    "shelves against the walls. Trophies and other symbols of "+
	    "victory and valour of Telberin fill the shelves proudly.\n\n");

   add_item( ({"tapestries", "hung tapestries", "tapestry"}),
	    "The beautiful tapestries depict arial views of the beauty and "+
	    "enormity of Telberin. One of the tapestries depicts this same "+
	    "view, only with valiant heros defending Telberin against "+
	    "Orcish invaders.\n");

   add_item( ({"second floor", "up", "turn", "bend"}),
	    "You try and peer up to the second floor, but can't see "+
	    "much as the stairwell bends around a slight turn and "+
	    "continues up into flickering lamplight.\n");

   add_item("shelves",
	    "The heavy, wooden shelves are astounding. The bottoms are "+
	    "at stepped angles and their backs are slightly curved so "+
	    "that they fit snugly against the wall along the stairwell "+
	    "and their contents remain level at all times. There are "+
	    "trophies and other proud symbols arranged carefully "+
	    "on the shelves.\n");

   add_item( ({"trophy", "trophies", "symbols"}),
	    "There are hundreds of trophies and symbols of pride, "+
	    "valour and victory. Some of the trophies are awards "+
	    "given to local knights for winning competitions, others "+
	    "are non-traditional trophies - such as a half-dozen "+
	    "horns of some foul beast, the stuffed and preserved hand "+
	    "of an enormous orc, and more.\n");

   add_exit(CASTLE_DIR + "2k1","up",0);
   add_exit(CASTLE_DIR + "1k9","south",0);
}

