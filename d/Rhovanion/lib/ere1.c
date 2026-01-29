#pragma save_binary

inherit "/d/Rhovanion/lib/field";

#include "/sys/macros.h"
#include "/d/Rhovanion/defs.h"

create_field()
{
        object door;

	set_area_desc("northern");
	set_area_type(12);
	set_area("river Running");
	set_land("Rhovanion");
	set_area_name("Erebor");
	set_grass_type("dark green grass.");

        door = clone_object(ERE_DIR + "door_ere1");
        door->move(TO);

	add_exit(ERE_DIR + "ere1", "south");
}