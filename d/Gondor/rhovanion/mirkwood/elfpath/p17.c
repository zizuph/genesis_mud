#include "../defs.h"

inherit MIRKWOOD_ELFPATH_DIR + "base";

void create_mirkwood_elfpath_room()
{
	set_room_seed(17);
	set_mirkwood_location(LOCATION_MIDDLE);

	::create_mirkwood_elfpath_room();

	set_add_wildlife();

    add_exit("p16", "west");
    add_exit("p18", "southeast");

    add_forest_entrance(MIRKWOOD_NORTH_FOREST_DIR + "r01/f16", "northwest");
    add_forest_entrance(MIRKWOOD_NORTH_FOREST_DIR + "r01/f17", "north");
    add_forest_entrance(MIRKWOOD_NORTH_FOREST_DIR + "r01/f18", "northeast");
    add_forest_entrance(MIRKWOOD_NORTH_FOREST_DIR + "r00/f18", "east");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r17/f16", "southwest");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r17/f17", "south");
    
}