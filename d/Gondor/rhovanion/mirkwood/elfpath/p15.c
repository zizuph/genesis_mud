#include "../defs.h"

inherit MIRKWOOD_ELFPATH_DIR + "base";

void create_mirkwood_elfpath_room()
{
	set_room_seed(15);
	set_mirkwood_location(LOCATION_MIDDLE);

	::create_mirkwood_elfpath_room();

	set_add_wildlife();

    add_exit("p14", "west");
    add_exit("p16", "east");

    add_forest_entrance(MIRKWOOD_NORTH_FOREST_DIR + "r01/f14", "northwest");
    add_forest_entrance(MIRKWOOD_NORTH_FOREST_DIR + "r01/f15", "north");
    add_forest_entrance(MIRKWOOD_NORTH_FOREST_DIR + "r01/f16", "northeast");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r17/f14", "southwest");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r17/f15", "south");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r17/f16", "southeast");
}