#include "../defs.h"

inherit MIRKWOOD_ELFPATH_DIR + "base";

void create_mirkwood_elfpath_room()
{
	set_room_seed(30);
	set_mirkwood_location(LOCATION_MIDDLE);

	::create_mirkwood_elfpath_room();

	set_add_wildlife();
    add_exit("p29", "west");
    add_exit("p31", "northeast");

    add_forest_entrance(MIRKWOOD_NORTH_FOREST_DIR + "r02/f29", "northwest");
    add_forest_entrance(MIRKWOOD_NORTH_FOREST_DIR + "r02/f30", "north");

    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r18/f29", "southwest");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r18/f30", "south");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r18/f31", "southeast");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r19/f31", "east");
    
}