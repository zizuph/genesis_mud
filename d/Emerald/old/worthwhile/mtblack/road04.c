/*
 * Road at the base of Mount Black and the Volcano
 * - Alaron January 1997
 */

#include "default.h"

inherit ROAD;

void
create_road()
{
    set_long("   You are standing at the foot of a towering, black "+
	     "mountain. Its peak is narrow and jagged and seems to "+
	     "reach up out of the east and touch the sky with its pointed "+
	     "tip. The black stone of the mountain is glistening with "+
	     "moisture from a recent rainfall. The road's gray, "+
	     "stone-covered surface continues to follow the base of the "+
	     "mountain heading generally northwest. Further north, the "+
	     "road passes the black mountain and follows along the base "+
	     "of the volcano. A dark, natural-looking entrance to a "+
	     "cave rests within the base of the mountain to the northeast.\n\n");

    add_item( ({"cave", "entrance", "dark entrance", "cave entrance",
		"dark cave", "dark cave entrance", "natural-looking entrance"}),
	     "The entrance to the cave looks quite natural. The moist, "+
	     "black stone of the mountain parts at a crack further up. The "+
	     "crack then spreads as it continues down the side of the "+
	     "mountain until it reaches the foot, where it has spread "+
	     "wide enough to allow people to enter.\n");

    add_exit(MBLACK_DIR + "road05", "north");
    add_exit(MBLACK_DIR + "road03", "south");
    add_exit(MBLACK_DIR + "cave/levela/entrance", "northeast", "@@cautious");
}

int
cautious()
{
    write("You cautiously step underneath the black stone and into "+
	  "the cave ... \n\n");
    say(QCTNAME(TP)+" cautiously steps underneath the black stone "+
	"and into the cave.\n");
    return 0;
}
