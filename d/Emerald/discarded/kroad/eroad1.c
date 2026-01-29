/*
 * eroad1.c
 * Kahlen Road
 * by Alaron August 31, 1996
 */

#include "defs.h"

inherit BASEROAD;

void
create_road()
{
    set_short("Packed dirt road");
    set_long("   The hard packed dirt road is overpowered by the sounds "+
	     "of water churning to the northwest. The salt breeze from the "+
	     "ocean blasts against the cliff face, causing a damp spray to "+
	     "drift over the road. Low bushes and green foliage ruffle in "+
	     "the soft breeze. Off to the north, beyond the low greenery, "+
	     "the foliage grows up to form the edge of a thick forest.\n\n");

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
		"vegetation"}),
	     "The bushes to the north of the path rustle gently in the "+
	     "cool sea breeze. There are various forms of plant life, "+
	     "including flowers, weeds, vines, and more. Some even "+
	     "look vaguely familiar.\n");

    add_item( ({"flowers", "weeds", "vines"}),
	     "There are several kinds of flowers growing amidst the "+
	     "low green bushes. Some of them even appear familiar.\n");

    add_item( ({"mill", "grist mill"}),
	     "Off in the distance to the northwest, you can see a large "+
	     "building through the trees accompanied by loud churning "+
	     "noises. It appears to be a grist mill.\n");

    add_exit(PATH + "road0", "west", 0, 1);
    add_exit(PATH + "eroad2", "east", 0, 1);
}
