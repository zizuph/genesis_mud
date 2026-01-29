#include "../defs.h"

inherit MIRKWOOD_ELFPATH_DIR + "base";

void create_mirkwood_elfpath_room()
{
	set_room_seed(6);
	set_mirkwood_location(LOCATION_WEST_PART);

	::create_mirkwood_elfpath_room();

	set_add_wildlife();

    add_exit("p05", "west");
    add_exit("p07", "east");

    add_forest_entrance(MIRKWOOD_NORTH_FOREST_DIR + "r01/f05", "northwest");
    add_forest_entrance(MIRKWOOD_NORTH_FOREST_DIR + "r01/f06", "north");
    add_forest_entrance(MIRKWOOD_NORTH_FOREST_DIR + "r01/f07", "northeast");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r17/f05", "southwest");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r17/f06", "south");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r17/f07", "southeast");
}