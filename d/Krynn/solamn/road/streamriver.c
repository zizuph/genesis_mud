/* Aridor, 08/98 */

#include "local.h"

inherit ROOM_BASE

void
create_road_room()
{
    set_short("An the river shore");
    set_long("You are on the shore of the Vingaard River, which is directly " +
	     "to your west. Here, a small stream coming from the plains from " +
	     "the east flows into the river.\n");
    add_item(({"river","vingaard river"}),
	     "This is the mighty Vingaard River, flowing through the Plains of " +
	     "Solamnia.\n");
    add_item(({"stream"}),
	     "This is a little stream coming from the east and flowing into " +
	     "the big river to the west.\n");
    add_item(({"plains","grass","bushes","tree","trees"}),
	     "The plains of Solamnia are covered with grass, bushes and the " +
	     "occasional tree.\n");

    if (LOAD_ERR(ROAD_OBJECT))
    {
	write("Bug! please report immediately...\n");
	return;
    }
    add_exit("", "east", "@@enter_map:" + ROAD_OBJECT + "|X@@",6,1);
    add_exit("", "south","@@enter_map:" + ROAD_OBJECT + "|X@@",6,1);
    add_exit("", "north","@@enter_map:" + ROAD_OBJECT + "|X@@",6,1);
}

