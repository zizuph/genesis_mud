#include "../defs.h"

inherit MIRKWOOD_ELFPATH_DIR + "base";

void create_mirkwood_elfpath_room()
{
	set_room_seed(27);
	set_mirkwood_location(LOCATION_MIDDLE);

	::create_mirkwood_elfpath_room();

	set_add_wildlife();

    add_exit("p26", "west");
    add_exit("p28", "east");

    add_forest_entrance(MIRKWOOD_NORTH_FOREST_DIR + "r02/f26", "northwest");
    add_forest_entrance(MIRKWOOD_NORTH_FOREST_DIR + "r02/f27", "north");
    add_forest_entrance(MIRKWOOD_NORTH_FOREST_DIR + "r02/f28", "northeast");

    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r18/f26", "southwest");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r18/f27", "south");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r18/f28", "southeast");

    
}