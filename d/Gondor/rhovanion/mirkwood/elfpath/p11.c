#include "../defs.h"

inherit MIRKWOOD_ELFPATH_DIR + "base";

void create_mirkwood_elfpath_room()
{
	set_room_seed(11);
	set_mirkwood_location(LOCATION_WEST_PART);

	::create_mirkwood_elfpath_room();

	set_add_wildlife();

    add_exit("p10", "west");
    add_exit("p12", "east");

    add_forest_entrance(MIRKWOOD_NORTH_FOREST_DIR + "r01/f10", "northwest");
    add_forest_entrance(MIRKWOOD_NORTH_FOREST_DIR + "r01/f11", "north");
    add_forest_entrance(MIRKWOOD_NORTH_FOREST_DIR + "r01/f12", "northeast");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r17/f10", "southwest");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r17/f11", "south");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r17/f12", "southeast");
}