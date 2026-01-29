#include "../defs.h"

inherit MIRKWOOD_ELFPATH_DIR + "base";

void create_mirkwood_elfpath_room()
{
	set_room_seed(16);
	set_mirkwood_location(LOCATION_MIDDLE);

	::create_mirkwood_elfpath_room();

	set_add_wildlife();

    add_exit("p15", "west");
    add_exit("p17", "east");

    add_forest_entrance(MIRKWOOD_NORTH_FOREST_DIR + "r01/f15", "northwest");
    add_forest_entrance(MIRKWOOD_NORTH_FOREST_DIR + "r01/f16", "north");
    add_forest_entrance(MIRKWOOD_NORTH_FOREST_DIR + "r01/f17", "northeast");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r17/f15", "southwest");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r17/f16", "south");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r17/f17", "southeast");
}