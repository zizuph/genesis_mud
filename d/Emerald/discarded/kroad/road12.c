/*
 * road12.c
 * Kahlen Road
 * by Alaron September 17, 1996
 */

#include "defs.h"

inherit BASEROAD;

void
create_road()
{
    set_short("Packed dirt road");
    set_long("   The hard-packed dirt road is a rounded curve here. It "+
	     "follows the edge of an enormous, thick forest heading "+
	     "east and continues to the south, where the road curves "+
	     "again, heading west. The forest borders the "+
	     "road between the packed dirt and the low, green foliage. On "+
	     "the opposite side of the forest lie the cliffs of the "+
	     "ocean inlet off to the south. You can hear the sound of "+
	     "water crashing against the rock far below.\n\n");

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
		"vegetation", "low greenery", "low foliage"}),
	     "The bushes to the north of the path rustle gently in the "+
	     "cool sea breeze. There are various forms of plant life, "+
	     "including flowers, weeds, vines, and more. Some even "+
	     "look vaguely familiar.\n");
    
    add_item( ({"flowers", "weeds", "vines"}),
	     "There are several kinds of flowers growing amidst the "+
	     "low green bushes. Some of them even appear familiar.\n");

    add_exit(PATH + "road11", "east", 0, 1);
    add_exit(PATH + "road13", "south", 0, 1);
}
