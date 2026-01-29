/*
 * Road at the base of Mount Black and the Volcano
 * - Alaron January 1997
 */

#include "default.h"

inherit ROAD;

void
create_road()
{
    set_long("   You are standing at the base of a tall, black "+
	     "mountain. Its black stone glistens with recent rainfall "+
	     "as it climbs up out of the earth and soars into the sky, its "+
	     "jagged peak standing against the backdrop of shifting "+
	     "clouds. A narrow mountain pass gently climbs up to the "+
	     "northeast onto the side of Mount Black. Looking further "+
	     "to the north, you notice the road begin to follow at the "+
	     "base of the volcano, winding around volcanic ash and black "+
	     "rock as it heads gradually northwest.\n\n");

    add_item( ({"ash", "volcanic ash", "rock", "black rock"}),
	     "The black rocks and bits of volcanic ash litter the road "+
	     "further north. You can't be sure when the ash and rocks "+
	     "fell from the volcano, but judging by the dark plume of "+
	     "smoke rising from the peak, you guess that it could have "+
	     "been recently.\n");

    add_item( ({"pass", "mountain pass", "narrow pass",
		"narrow mountain pass"}),
	     "The narrow mountain pass climbs up the side of Mount Black "+
	     "at an easy pace, heading generally northeast.\n");

    add_exit(MBLACK_DIR + "road06", "north",0, 1);
    add_exit(MBLACK_DIR + "pass/mb1", "northeast", 0, 3);
    add_exit(MBLACK_DIR + "road04", "south",0,1);
}
