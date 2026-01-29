#include "../defs.h"

inherit MIRKWOOD_ELFPATH_DIR + "base";

void create_mirkwood_elfpath_room()
{
	set_room_seed(22);
	set_mirkwood_location(LOCATION_MIDDLE);

	::create_mirkwood_elfpath_room();

	set_add_wildlife();

    add_exit("p21", "west");
    add_exit("p23", "northeast");

    
    add_forest_entrance(MIRKWOOD_NORTH_FOREST_DIR + "r00/f21", "northwest");
    add_forest_entrance(MIRKWOOD_NORTH_FOREST_DIR + "r00/f22", "north");

    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r17/f23", "east");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r16/f21", "southwest");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r16/f22", "south");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r16/f23", "southeast");
}