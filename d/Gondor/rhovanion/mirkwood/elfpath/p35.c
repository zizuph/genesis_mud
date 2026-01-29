#include "../defs.h"

inherit MIRKWOOD_ELFPATH_DIR + "base";

void create_mirkwood_elfpath_room()
{
	set_room_seed(35);
	set_mirkwood_location(LOCATION_EAST_EDGE);

	::create_mirkwood_elfpath_room();

	set_add_wildlife();

    add_exit("p34", "west");
    add_exit("p36", "northeast");

    add_forest_entrance(MIRKWOOD_NORTH_FOREST_DIR + "r03/f34", "northwest");

    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r19/f34", "southwest");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r19/f35", "south");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r19/f36", "southeast");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r20/f36", "east");
    
}