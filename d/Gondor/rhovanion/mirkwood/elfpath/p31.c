#include "../defs.h"

inherit MIRKWOOD_ELFPATH_DIR + "base";

void create_mirkwood_elfpath_room()
{
	set_room_seed(31);
	set_mirkwood_location(LOCATION_MIDDLE);

	::create_mirkwood_elfpath_room();

	set_add_wildlife();

    add_exit("p30", "southwest");
    add_exit("p32", "east");

    add_forest_entrance(MIRKWOOD_NORTH_FOREST_DIR + "r03/f30", "northwest");
    add_forest_entrance(MIRKWOOD_NORTH_FOREST_DIR + "r03/f31", "north");
    add_forest_entrance(MIRKWOOD_NORTH_FOREST_DIR + "r03/f32", "northeast");
    add_forest_entrance(MIRKWOOD_NORTH_FOREST_DIR + "r02/f30", "west");
    
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r19/f31", "south");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r19/f32", "southeast");

    
}