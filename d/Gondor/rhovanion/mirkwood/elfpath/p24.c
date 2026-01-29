#include "../defs.h"

inherit MIRKWOOD_ELFPATH_DIR + "base";

void create_mirkwood_elfpath_room()
{
	set_room_seed(24);
	set_mirkwood_location(LOCATION_MIDDLE);

	::create_mirkwood_elfpath_room();

	set_add_wildlife();

    add_exit("p23", "west");
    add_exit("p25", "east");

    add_forest_entrance(MIRKWOOD_NORTH_FOREST_DIR + "r01/f23", "northwest");
    add_forest_entrance(MIRKWOOD_NORTH_FOREST_DIR + "r01/f24", "north");
    add_forest_entrance(MIRKWOOD_NORTH_FOREST_DIR + "r01/f25", "northeast");

    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r17/f23", "southwest");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r17/f24", "south");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r17/f25", "southeast");

    
}