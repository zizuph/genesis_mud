#include "../defs.h"

inherit MIRKWOOD_ELFPATH_DIR + "base";

void create_mirkwood_elfpath_room()
{
	set_room_seed(39);
	set_mirkwood_location(LOCATION_EAST_PART);

	::create_mirkwood_elfpath_room();

	set_add_wildlife();

    add_exit("p38", "west");
    add_exit("p40", "east");
}