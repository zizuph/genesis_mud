#include "../defs.h"

inherit MIRKWOOD_ELFPATH_DIR + "base";

void create_mirkwood_elfpath_room()
{
	set_room_seed(4);
	set_mirkwood_location(LOCATION_WEST_EDGE);

	::create_mirkwood_elfpath_room();

	set_add_wildlife();

    add_exit("p03", "west");
    add_exit("p05", "east");

    add_forest_entrance(MIRKWOOD_NORTH_FOREST_DIR + "r01/f03", "northwest");
    add_forest_entrance(MIRKWOOD_NORTH_FOREST_DIR + "r01/f04", "north");
    add_forest_entrance(MIRKWOOD_NORTH_FOREST_DIR + "r01/f05", "northeast");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r17/f03", "southwest");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r17/f04", "south");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r17/f05", "southeast");
}