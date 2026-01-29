#include "../defs.h"

inherit MIRKWOOD_ELFPATH_DIR + "base";

void create_mirkwood_elfpath_room()
{
	set_room_seed(2);
	set_mirkwood_location(LOCATION_WEST_EDGE);

	::create_mirkwood_elfpath_room();

	set_add_wildlife();

    add_exit("p01", "west");
    add_exit("p03", "east");

    add_exit(VALE_DIR + "valen18w6", "southwest", 0,2,1);

    add_forest_entrance(MIRKWOOD_NORTH_FOREST_DIR + "r01/f01", "northwest");
    add_forest_entrance(MIRKWOOD_NORTH_FOREST_DIR + "r01/f02", "north");
    add_forest_entrance(MIRKWOOD_NORTH_FOREST_DIR + "r01/f03", "northeast");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r17/f02", "south");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r17/f03", "southeast");
}