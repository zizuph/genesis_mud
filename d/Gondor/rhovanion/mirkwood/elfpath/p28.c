#include "../defs.h"

inherit MIRKWOOD_ELFPATH_DIR + "base";

void create_mirkwood_elfpath_room()
{
	set_room_seed(28);
	set_mirkwood_location(LOCATION_MIDDLE);

	::create_mirkwood_elfpath_room();

	set_add_wildlife();

    add_exit("p27", "west");
    add_exit("p29", "east");

    add_forest_entrance(MIRKWOOD_NORTH_FOREST_DIR + "r02/f27", "northwest");
    add_forest_entrance(MIRKWOOD_NORTH_FOREST_DIR + "r02/f28", "north");
    add_forest_entrance(MIRKWOOD_NORTH_FOREST_DIR + "r02/f29", "northeast");

    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r18/f27", "southwest");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r18/f28", "south");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r18/f29", "southeast");

    
}