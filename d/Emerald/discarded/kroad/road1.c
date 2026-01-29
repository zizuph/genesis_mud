/*
 * road1.c
 * Kahlen Road
 * by Alaron August September 17, 1996
 */

#include "defs.h"

inherit BASEROAD;

void
create_road()
{
    set_short("Packed dirt road");
    set_long("   The chill, salt air drifts up from the cliffs to the south, "+
	     "its spray covering the path in a damp mist. The low bushes "+
	     "and green foliage blow back gently in the breeze. The north "+
	     "side of the road is seemingly under attack by a flood of "+
	     "low vegetation, stretching toward the cliffs and the "+
	     "puddles of water in that direction. Beyond the low "+
	     "vegetation lies the rim of a great forest, looming ominously "+
	     "in the distance. The path winds its way through the trees "+
	     "and alongside the cliffs as it continues to the east and "+
	     "west.\n\n");

    OUTSIDE;
    LIGHT(1);
    
    add_item( ({"cliffs", "south"}),
	     "The white and gray cliffs to the south rise up out of the "+
	     "ocean at a steep angle. As the cliffs recede into the "+
	     "mountainside, growth and vegetation begin to appear until "+
	     "farther to the north it escalates into the edge of a "+
	     "forest. As you examine the cliffs, you can "+
	     "hear the sounds of water crashing against the rocks "+
	     "far below.\n");

    add_item( ({"bushes", "low bushes", "foliage", "green foliage",
		"vegetation", "low vegetation"}),
	     "The bushes to the north of the path rustle gently in the "+
	     "cool sea breeze. There are various forms of plant life, "+
	     "including flowers, weeds, vines, and more. Some even "+
	     "look vaguely familiar.\n");

    add_item( ({"flowers", "weeds", "vines"}),
	     "There are several kinds of flowers growing amidst the "+
	     "low green bushes. Some of them even appear familiar.\n");

    add_item( ({"mill", "grist mill"}),
	     "Off in the distance to the northeast, you can see a large "+
	     "building through the trees accompanied by loud churning "+
	     "noises. It appears to be a grist mill.\n");

    add_exit(PATH + "road2", "west", 0, 1);
    add_exit(PATH + "road0", "east", 0, 1);
}
