#include "../defs.h"

inherit MIRKWOOD_ELFPATH_DIR + "base";

void create_mirkwood_elfpath_room()
{
	set_room_seed(9);
	set_mirkwood_location(LOCATION_WEST_PART);

	::create_mirkwood_elfpath_room();

	set_add_wildlife();

    add_exit("p08", "west");
    add_exit("p10", "east");

    add_forest_entrance(MIRKWOOD_NORTH_FOREST_DIR + "r01/f08", "northwest");
    add_forest_entrance(MIRKWOOD_NORTH_FOREST_DIR + "r01/f09", "north");
    add_forest_entrance(MIRKWOOD_NORTH_FOREST_DIR + "r01/f10", "northeast");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r17/f08", "southwest");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r17/f09", "south");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r17/f10", "southeast");
}