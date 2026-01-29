#include "../defs.h"

inherit MIRKWOOD_ELFPATH_DIR + "base";

void create_mirkwood_elfpath_room()
{
	set_room_seed(23);
	set_mirkwood_location(LOCATION_MIDDLE);

	::create_mirkwood_elfpath_room();

	set_add_wildlife();

    add_exit("p22", "southwest");
    add_exit("p24", "east");

    add_forest_entrance(MIRKWOOD_NORTH_FOREST_DIR + "r01/f22", "northwest");
    add_forest_entrance(MIRKWOOD_NORTH_FOREST_DIR + "r01/f23", "north");
    add_forest_entrance(MIRKWOOD_NORTH_FOREST_DIR + "r01/f24", "northeast");
    add_forest_entrance(MIRKWOOD_NORTH_FOREST_DIR + "r00/f22", "west");
    
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r17/f23", "south");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r17/f24", "southeast");

    
}