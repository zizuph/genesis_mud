#include "../defs.h"

inherit MIRKWOOD_ELFPATH_DIR + "base";

void create_mirkwood_elfpath_room()
{
	set_room_seed(32);
	set_mirkwood_location(LOCATION_EAST_PART);

	::create_mirkwood_elfpath_room();

	set_add_wildlife();

    add_exit("p31", "west");
    add_exit("p33", "east");

    add_forest_entrance(MIRKWOOD_NORTH_FOREST_DIR + "r03/f31", "northwest");
    add_forest_entrance(MIRKWOOD_NORTH_FOREST_DIR + "r03/f32", "north");
    add_forest_entrance(MIRKWOOD_NORTH_FOREST_DIR + "r03/f33", "northeast");

    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r19/f31", "southwest");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r19/f32", "south");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r19/f33", "southeast");

    
}