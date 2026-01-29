/*
 * road22.c
 * Kahlen Road
 * by Alaron September 17, 1996
 */

#include "defs.h"

inherit BASEROAD;

void
create_road()
{
    set_short("Forest clearing");
    set_long("   You are standing in the middle of an enormous clearing "+
	     "in the middle of a forest. The road which leads out of the "+
	     "clearing to the north gradually opens up into this circular-"+
	     "shaped clearing. The dirt here is damp but still loose "+
	     "and thick. There is a thick layer of low greenery which "+
	     "rests between the edge of the dirt and the forest rim. "+
	     "A cool breeze drifts into the area from the "+
	     "north, creating a soft whistling sound as it passes "+
             "between the leaves and thick trunks of the forest trees. "+
              "You notice a very small, overgrown path leading out of "+
              "the clearing to the southwest.\n\n");
    
    OUTSIDE;
    LIGHT(1);

    remove_item("forest");

    add_item(({"leaves","trees","forest"}),
	     "The thick forest here is thick and lush, its green color "+
	     "dominating the view in all directions. There is a small "+
	     "opening in the forest wall to the north where the narrow "+
	     "road leads out of the clearing.\n");

    add_item( ({"bushes", "low bushes", "foliage", "green foliage",
		"vegetation", "greenery", "low greenery"}),
	     "The bushes surrounding the clearing rustle gently in the "+
	     "cool breeze. There are various forms of plant life, "+
	     "including flowers, weeds, vines, and more. Some even "+
	     "look vaguely familiar.\n");

    add_item( ({"flowers", "weeds", "vines"}),
	     "There are several kinds of flowers growing amidst the "+
	     "low green bushes. Some of them even appear familiar.\n");

    add_item( ({"path", "small path"}),
              "The small path is narrow and overgrown. You barely even "+
              "notice that it is there. You can't quite make out what is "+
              "on the other side of it.\n");
    add_exit(PATH + "road21", "north", 0, 2);
    add_exit(TELSERON_DIR + "forest_edge", "southwest", 0, 4);
}
