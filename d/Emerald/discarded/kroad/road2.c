/*
 * road2.c
 * Kahlen Road
 * by Alaron August 31, 1996
 */

#include "defs.h"

inherit BASEROAD;

void
create_road()
{
    set_short("Packed dirt road");
    set_long("   A cool, salty breeze drifts up from cliffs to the south "+
	     "and across the path. The low bushes and green foliage ruffles "+
	     "gently against the breeze. Off in the distance to the north "+
	     "the low vegetation grows into the edge of a thick forest. The "+
	     "path continues parallel to the cliff side heading south "+
	     "and east.\n\n");

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
		"vegetation"}),
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

    
    /* Note the 1 as the last parameter. This is the fatigue
     * factor. This is a supposed default ,but I don't trust them
     * to stay the same. Higher values make it more 'tiring' to walk
     * through the exit.
     */

    add_exit(PATH + "road3", "south", 0, 1);
    add_exit(PATH + "road1", "east", 0, 1);
}
