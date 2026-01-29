#include "../defs.h"

inherit MIRKWOOD_ELFPATH_DIR + "base";

void create_mirkwood_elfpath_room()
{
	set_room_seed(26);
	set_mirkwood_location(LOCATION_MIDDLE);

	::create_mirkwood_elfpath_room();

	set_add_wildlife();

    add_exit("p25", "southwest");
    add_exit("p27", "east");

    add_forest_entrance(MIRKWOOD_NORTH_FOREST_DIR + "r02/f25", "northwest");
    add_forest_entrance(MIRKWOOD_NORTH_FOREST_DIR + "r02/f26", "north");
    add_forest_entrance(MIRKWOOD_NORTH_FOREST_DIR + "r02/f27", "northeast");
    add_forest_entrance(MIRKWOOD_NORTH_FOREST_DIR + "r01/f25", "west");
    
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r18/f26", "south");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r18/f27", "southeast");

    
}