/* Aridor, 08/98 */

#include "local.h"

inherit ROOM_BASE

void
create_road_room()
{
    set_short("At a waterfall");
    set_long("The plains stretch out around you, and even though " +
	     "they appear really flat, there are still ever so slight " +
	     "undulations. One of bigger inclinations can be seen here, and " +
	     "the mighty Vingaard River to your west has to pass this " +
	     "drop as well. The total difference is only about 2 metres, " +
	     "and the inclination quickly vanishes into the " +
	     "surrounding landscape, but there is a waterfall here nonetheless. " +
	     "The river appears to be very shallow right at the top of the " +
	     "waterfall, allowing passage across the river to the west. " +
	     "A small stream arrives from the east, adding a negligible " +
	     "amount of water to the broad river.\n");
    add_item(({"plains","inclination","rise"}),
            "The wide plains stretch out before you here, rising up " +
            "along an inclination of about 2 meters. The rise has " +
            "created a short waterfall just west of here, where the " +
            "Vingaard River tumbles over it.\n");
    add_item(({"waterfall"}), "The Vingaard River rushes over a small cliff " +
            "just west of here, cascading down in a spectacular waterfall. " +
            "The river appears to be shallow enough here to serve as a " +
            "natural ford.\n");
    add_item(({"river", "vingaard river", "shore"}),
            "The shore is down at the bottom a small cliff, and you can't " +
            "see any way to reach the water from here.\n");
    add_item(({"stream"}), "This is a small stream, barely more than " +
            "a trickle, bubbling merrily along through the plains.\n");
    add_item(({"ford"}), "The river appears to be very shallow, " +
            "if a bit swift, at the top of the waterfall here, " +
            "creating what appears to be a natural ford.\n");

    add_exit("waterfall2.c", "west", "@@closed@@",6,1);

    if (LOAD_ERR(ROAD_OBJECT))
    {
	write("Bug! please report immediately...\n");
	return;
    }
    add_exit("", "east", "@@enter_map:" + ROAD_OBJECT + "|W@@",6,1);
    add_exit("", "south","@@enter_map:" + ROAD_OBJECT + "|W@@",6,1);
}

int
closed()
{
    write("You make your way forward across the river, but the current " +
	  "is much stronger than what it appeared to be and what you can " +
	  "handle. You barely make it back to the shore.\n");
    return 1;
}
