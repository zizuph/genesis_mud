/*
* road6.c
* Kahlen Road
* by Alaron September 17, 1996
*/

#include "defs.h"

inherit BASEROAD;

void
create_road()
{
   set_short("Packed dirt road");
   set_long("   The salt air from the ocean drifts up and over the edges "+
	    "of the cliffs. The road here continues away from the cliffs "+
	    "and toward a thick forest to the north and curves to the west. "+
	    "A small branch of the road continues to the south as the "+
	    "road heads east from here. The road is bordered on the south "+
	    "and east by cliffs, and on the north by low, green vegetation "+
	    "which eventually gives way to the rim of a thick forest.\n\n");

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
	       "vegetation", "low vegetation", "green vegetation",
	       "low foliage"}),
	    "The bushes to the north of the path rustle gently in the "+
	    "cool sea breeze. There are various forms of plant life, "+
	    "including flowers, weeds, vines, and more. Some even "+
	    "look vaguely familiar.\n");
   
   add_item( ({"flowers", "weeds", "vines"}),
	    "There are several kinds of flowers growing amidst the "+
	    "low green bushes. Some of them even appear familiar.\n");
      
   add_exit(PATH + "road5", "east", 0, 1);
   add_exit(PATH + "road7", "south", 0, 1);
   add_exit(PATH + "road8", "north", 0, 1);
}
