/*
* road8.c
* Kahlen Road
* by Alaron September 17, 1996
*/

#include "defs.h"

inherit BASEROAD;

void
create_road()
{
    set_short("Packed dirt road");
    set_long("   The hard-packed dirt road is almost completely surrounded "+
      "by trees and forest here. The edge of the road is bordered "+
      "by low, green foliage. A few yards beyond the low foliage "+
      "is the rim of an enormous, thick forest. The sounds of "+
      "various forest animals can be heard echoing out of the "+
      "darkness between the trees. The sound of water crashing "+
      "against rock face can be heard to the south beyond the "+
      "cliffs. The main road continues to the west and south.\n\n");

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
	"vegetation", "low vegetation", "low foliage"}),
      "The bushes surrounding the road rustle gently in the "+
      "cool sea breeze. There are various forms of plant life, "+
      "including flowers, weeds, vines, and more. Some even "+
      "look vaguely familiar.\n");

    add_item( ({"flowers", "weeds", "vines"}),
      "There are several kinds of flowers growing amidst the "+
      "low green bushes. Some of them even appear familiar.\n");

    add_exit(PATH + "road6", "south", 0, 1);
    add_exit(PATH + "road9", "west", 0, 1);
}
