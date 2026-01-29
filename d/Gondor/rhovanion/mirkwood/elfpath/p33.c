#include "../defs.h"

inherit MIRKWOOD_ELFPATH_DIR + "base";

void create_mirkwood_elfpath_room()
{
	set_room_seed(33);
	set_mirkwood_location(LOCATION_EAST_PART);

	::create_mirkwood_elfpath_room();

	set_add_wildlife();

    add_exit("p32", "west");
    add_exit("p34", "east");

    add_forest_entrance(MIRKWOOD_NORTH_FOREST_DIR + "r03/f32", "northwest");
    add_forest_entrance(MIRKWOOD_NORTH_FOREST_DIR + "r03/f33", "north");
    add_forest_entrance(MIRKWOOD_NORTH_FOREST_DIR + "r03/f34", "northeast");

    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r19/f32", "southwest");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r19/f33", "south");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r19/f34", "southeast");

    
}