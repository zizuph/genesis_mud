#include "../defs.h"

inherit MIRKWOOD_ELFPATH_DIR + "base";

void create_mirkwood_elfpath_room()
{
	set_room_seed(42);
	set_mirkwood_location(LOCATION_EAST_PART);

	::create_mirkwood_elfpath_room();

	set_add_wildlife();

    add_exit("p41", "west");
    add_exit("p43", "southeast");

}