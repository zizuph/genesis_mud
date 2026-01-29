#include "../defs.h"

inherit MIRKWOOD_ELFPATH_DIR + "base";

void create_mirkwood_elfpath_room()
{
	set_room_seed(18);
	set_mirkwood_location(LOCATION_MIDDLE);

	::create_mirkwood_elfpath_room();

	set_add_wildlife();

    add_exit("p17", "northwest");
    add_exit("p19", "east");

    
    add_forest_entrance(MIRKWOOD_NORTH_FOREST_DIR + "r00/f18", "north");
    add_forest_entrance(MIRKWOOD_NORTH_FOREST_DIR + "r00/f19", "northeast");

    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r17/f17", "west");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r16/f17", "southwest");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r16/f18", "south");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r16/f19", "southeast");
    
}