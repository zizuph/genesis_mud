#include "../defs.h"

inherit MIRKWOOD_ELFPATH_DIR + "base";

void create_mirkwood_elfpath_room()
{
	set_room_seed(19);
	set_mirkwood_location(LOCATION_MIDDLE);

	::create_mirkwood_elfpath_room();

	set_add_wildlife();

    add_exit("p18", "west");
    add_exit("p20", "east");

    add_forest_entrance(MIRKWOOD_NORTH_FOREST_DIR + "r00/f18", "northwest");
    add_forest_entrance(MIRKWOOD_NORTH_FOREST_DIR + "r00/f19", "north");
    add_forest_entrance(MIRKWOOD_NORTH_FOREST_DIR + "r00/f20", "northeast");

    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r16/f18", "southwest");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r16/f19", "south");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r16/f20", "southeast");
    
}