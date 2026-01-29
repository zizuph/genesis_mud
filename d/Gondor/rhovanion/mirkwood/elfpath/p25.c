#include "../defs.h"

inherit MIRKWOOD_ELFPATH_DIR + "base";

void create_mirkwood_elfpath_room()
{
	set_room_seed(25);
	set_mirkwood_location(LOCATION_MIDDLE);

	::create_mirkwood_elfpath_room();

	set_add_wildlife();

    add_exit("p24", "west");
    add_exit("p26", "northeast");

    add_forest_entrance(MIRKWOOD_NORTH_FOREST_DIR + "r01/f24", "northwest");
    add_forest_entrance(MIRKWOOD_NORTH_FOREST_DIR + "r01/f25", "north");

    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r17/f24", "southwest");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r17/f25", "south");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r17/f26", "southeast");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r18/f26", "east");
    
}