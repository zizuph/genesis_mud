/*
 * Road at the base of Mount Black and the Volcano
 * - Alaron January 1997
 */

#include "default.h"

inherit ROAD;

void
create_road()
{
    set_long("   The road here widens and has several large, dark "+
	     "green bushes growing around the side of it. The base of "+
	     "the volcano shifts away from the road here, allowing some "+
	     "relief from the stifling force of the volcanic ash and "+
	     "rock. As the road continues north, it dips down into "+
	     "a clearing amidst some small trees near the coastline. Beyond "+
	     "that there are two enormous piers out on the water. A narrow "+
	     "strip of forest runs east between the coastline and the "+
	     "volcano. Once farther east than the volcano, you can see "+
	     "the forest grow and expand to incredible proportions.\n\n");

    add_item( ({"clearing", "trees", "small trees", "coastline"}),
	     "The coastline just to the north is calm. You can't quite "+
	     "be sure why there are no waves, but you think it might "+
	     "have something to do with a barrier reef further out "+
	     "to sea.\n");

    add_item( ({"forest", "strip of forest", "narrow strip"}),
	     "The strip of forest is narrow between the volcano and "+
	     "the coastline. Once the forest has enough room to "+
	     "expand to the east beyond the volcano, you can see it "+
	     "stretch to an incredible size, consuming the entire "+
	     "coastline.\n");

    add_exit(VOLCANO_DIR + "clear", "north");
    add_exit(MBLACK_DIR + "road08", "south");
}
