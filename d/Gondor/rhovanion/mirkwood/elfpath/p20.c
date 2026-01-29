#include "../defs.h"

inherit MIRKWOOD_ELFPATH_DIR + "base";

void create_mirkwood_elfpath_room()
{
	set_room_seed(20);
	set_mirkwood_location(LOCATION_MIDDLE);

	::create_mirkwood_elfpath_room();

	set_add_wildlife();

    add_exit("p19", "west");
    add_exit("p21", "east");

    add_forest_entrance(MIRKWOOD_NORTH_FOREST_DIR + "r00/f19", "northwest");
    add_forest_entrance(MIRKWOOD_NORTH_FOREST_DIR + "r00/f20", "north");
    add_forest_entrance(MIRKWOOD_NORTH_FOREST_DIR + "r00/f21", "northeast");

    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r16/f19", "southwest");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r16/f20", "south");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r16/f21", "southeast");
    
}