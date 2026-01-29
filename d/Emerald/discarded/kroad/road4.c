/*
 * road4.c
 * Kahlen Road
 * by Alaron September 17, 1996
 */

#include "defs.h"

inherit BASEROAD;

void
create_road()
{
    set_short("Packed dirt road");
    set_long("   A cool, salt breeze blows up against the cliff face, "+
	     "sending a damp spray across the hard-packed dirt road. Small "+
	     "puddles dot the edge of the road near the cliffs. Low bushes "+
	     "and green foliage ruffle gently in the breeze, bordering "+
	     "the northern edge of the road between it and an enormous "+
	     "forest. The road continues along the edge of the cliffs to "+
	     "the east and west.\n\n");

    OUTSIDE;
    LIGHT(1);

    add_item( ({"puddles", "small puddles"}),
	     "Small puddles dot the landscape just beyond the southern "+
	     "edge of the road. The sea spray blowing up against the "+
	     "cliff face has dropped enough moisture on the road to "+
	     "form little clusters of sea water puddles.\n");

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

    add_exit(PATH + "road5", "west", 0, 1);
    add_exit(PATH + "road3", "east", 0, 1);
}
