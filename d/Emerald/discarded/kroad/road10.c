/*
* road10.c
* Kahlen Road
* by Alaron September 17, 1996
*/

#include "defs.h"

inherit BASEROAD;

void
create_road()
{
    set_short("Packed dirt road");
    set_long("   The hard-packed dirt road runs along the edge of an "+
      "enormous, thick forest to the north. The sounds of forest "+
      "animals can be heard from deep within its borders. Beyond "+
      "the road as it curves to the west just south of here, you "+
      "can see the edges of the cliffs and hear the sound of water "+
      "crashing against the rocks. The road is bordered by low, "+
      "green vegetation and greenery, which eventually gives way "+
      "to the forest rim.\n\n");

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
	"vegetation", "low vegetation", "greenery"}),
      "The bushes to the north of the path rustle gently in the "+
      "cool sea breeze. There are various forms of plant life, "+
      "including flowers, weeds, vines, and more. Some even "+
      "look vaguely familiar.\n");

    add_item( ({"flowers", "weeds", "vines"}),
      "There are several kinds of flowers growing amidst the "+
      "low green bushes. Some of them even appear familiar.\n");

    add_exit(PATH + "road11", "south", 0, 1);
    add_exit(PATH + "road9", "east", 0, 1);
}
