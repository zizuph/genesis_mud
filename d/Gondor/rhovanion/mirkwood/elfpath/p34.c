#include "../defs.h"

inherit MIRKWOOD_ELFPATH_DIR + "base";

void create_mirkwood_elfpath_room()
{
	set_room_seed(34);
	set_mirkwood_location(LOCATION_EAST_PART);

	::create_mirkwood_elfpath_room();

	set_add_wildlife();

    add_exit("p33", "west");
    add_exit("p35", "east");

    add_forest_entrance(MIRKWOOD_NORTH_FOREST_DIR + "r03/f33", "northwest");
    add_forest_entrance(MIRKWOOD_NORTH_FOREST_DIR + "r03/f34", "north");

    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r19/f33", "southwest");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r19/f34", "south");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r19/f35", "southeast");

    
}