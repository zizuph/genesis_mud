#include "../defs.h"

inherit MIRKWOOD_ELFPATH_DIR + "base";

void create_mirkwood_elfpath_room()
{
	set_room_seed(1);
	set_mirkwood_location(LOCATION_WEST_EDGE);

	::create_mirkwood_elfpath_room();

	set_add_wildlife();

    add_exit("p02", "east");
    add_exit(VALE_DIR + "valen19w7", "west", "@@exit@@");
    add_exit(VALE_DIR + "valen18w6", "south", 0,2,1);
    add_exit(VALE_DIR + "valen18w7", "southwest", 0,2,1);
    add_exit(VALE_DIR + "valen20w7", "northwest","@@block@@",2,1);
    add_forest_entrance(MIRKWOOD_NORTH_FOREST_DIR + "r01/f01", "north");
    add_forest_entrance(MIRKWOOD_NORTH_FOREST_DIR + "r01/f02", "northeast");
    add_forest_entrance(MIRKWOOD_CENTRAL_FOREST_DIR + "r17/f02", "southeast");
}

int
exit()
{
write("You pass beneath the forest gate and enter into the valley " +
    "of the Anduin river.\n");
return 0;
}

int
block()
{
write("The Anduin river appears to have flooded its banks, a soggy " +
    "marsh extending all the way to the trees of Mirkwood. You cannot " +
    "find any passage north from here.\n");
return 1;
}