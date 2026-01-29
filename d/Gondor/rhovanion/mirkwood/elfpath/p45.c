#include "../defs.h"

inherit MIRKWOOD_ELFPATH_DIR + "base";

void create_mirkwood_elfpath_room()
{
	set_room_seed(45);
	set_mirkwood_location(LOCATION_EAST_EDGE);

	::create_mirkwood_elfpath_room();

	set_add_wildlife();
	
    add_exit("p44", "northwest");
    add_exit("p46", "east");

}