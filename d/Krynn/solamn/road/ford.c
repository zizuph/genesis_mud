/* Aridor, 08/98 */

#include "local.h"

inherit ROOM_BASE
inherit CONQUER_BASE

int
no_pass()
{
    write("The ford is not yet passable.\n");
    return 1;
}

void
create_road_room()
{
    set_short("At the Vingaard River");
    set_long("This is the eastern shore of the Vingaard River. " +
        "The river is flowing from south to north. The water at this " +
        "spot on the river is very low, and a track leads down into " +
        "the river. The track leads out again on the other side.\n");
    add_item(({"track", "ford", "river", "vingaard river", "water"}), 
        "This appears to be a ford across the Vingaard River, with a " +
        "track entering the river here, and emerging again on the other " +
        "side.\n");
    add_item(({"shore", "eastern shore"}), "The water of the river " +
        "laps softly onto the shore.\n");

    if (LOAD_ERR(ROAD_OBJECT))
    {
        write("Bug! please report immediately.\n");
	return;
    }

    add_exit("", "east", "@@enter_map:" + ROAD_OBJECT + "|F@@",6,1);
    add_exit("", "south","@@enter_map:" + ROAD_OBJECT + "|F@@",6,1);
    add_exit("", "north","@@enter_map:" + ROAD_OBJECT + "|F@@",6,1); 
    add_exit("beyond_ford","west","@@no_pass@@",6);
}

void
init()
{
    init_conquer();
    ::init();
}

void
reset_road_room()
{
    reset_conquer_room();
}
