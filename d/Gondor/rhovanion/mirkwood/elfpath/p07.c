#include "../defs.h"

inherit MIRKWOOD_ELFPATH_DIR + "base";

void create_mirkwood_elfpath_room()
{
	set_room_seed(7);
	set_mirkwood_location(LOCATION_WEST_PART);

	::create_mirkwood_elfpath_room();

	set_add_wildlife();

    add_exit("p06", "west");
    add_exit("p08", "east");

    add_forest_entrance(MIRKWOOD_NORTH_FOREST_DIR + "r01/f06", "northwest");
    add_forest_entrance(MIRKWOOD_NORTH_FOREST_DIR + "r01/f07", "north");
    add_forest_entrance(MIRKWOOD_NORTH_FOREST_DIR + "r01/f08", "northeast");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r17/f06", "southwest");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r17/f07", "south");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r17/f08", "southeast");
}